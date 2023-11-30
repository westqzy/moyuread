// The module 'vscode' contains the VS Code extensibility API
// Import the module and reference it with the alias vscode in your code below
const vscode = require('vscode')
const path = require("path")
const fs = require("fs")
//const tpl = require("./muban.c")
// 读书模式
let read_mode =  1;
let muban = 'muban.c'
let novel_name = 'xc4210_self_test.c'
// 每次显示几行
let hang_1 = 2;
let hang = 2;
// 小说地址
let books_dir = ""
// const userSetting = vscode.workspace.getConfiguration().get('yourExtension.parameter', 'default-value');
let fake_work = `
if(D[i] != A[i])
{
    testcase_fail();
}
`;
let fake_work2 = `
else if(i < 8)
{
    if(B[i] != C[i])
    {
        testcase_fail();
    }
}
`;
// 获取行数
let fake_work_lines = fake_work.split('\n').length-2;
let novelPath = ''
let env = null
// 小说内容按行存储
let novelLines = []
// let boolChange = 0
// 总共的页码
let totalPage = 0
// 底部状态栏按键
let processBar = null
let nextBar = null
let prevBar = null
let jumpBar = null
let changeBar = null
let lineNumber = hang_1+1;
// This method is called when your extension is activated
// Your extension is activated the very first time the command is executed
// 字符串占位符

String.prototype.format = function () {
	if (arguments.length == 0) return this;
	var param = arguments[0];
	var s = this;
	if (typeof (param) == 'object') {
	  for (var key in param)
		s = s.replace(new RegExp("\\{" + key + "\\}", "g"), param[key]);
	  return s;
	} else {
	  for (var i = 0; i < arguments.length; i++)
		s = s.replace(new RegExp("\\{" + i + "\\}", "g"), arguments[i]);
	  return s;
	}
  }
/**
 * @param {vscode.ExtensionContext} context
 */
function activate(context) {
	// Use the console to output diagnostic information (console.log) and errors (console.error)
	// This line of code will only be executed once when your extension is activated
	console.log('Congratulations, your extension "moyuread" is now active!');

	// The command has been defined in the package.json file
	// Now provide the implementation of the command with  registerCommand
	// The commandId parameter must match the command field in package.json
	get_setting_value();
	init();
	let open = vscode.commands.registerCommand('moyuread.openNovel', function () {
		//vscode.window.showInformationMessage("HELLO");
		// The code you place here will be executed every time your command is executed
			// 获取当前活动的文本编辑器实例
		get_setting_value();
		init2();	
		const options = {
			// 选中第3行第9列到第3行第17列
			//selection: new vscode.Range(new vscode.Position(2, 8), new vscode.Position(2, 16));
			// 是否预览，默认true，预览的意思是下次再打开文件是否会替换当前文件
			//preview: false,
			// 显示在第一个编辑器
			viewColumn: vscode.ViewColumn.One 
		};
		// Display a message box to the user
		//vscode.window.showInformationMessage('Hello World from MoyuRead!');
		vscode.window.showTextDocument(vscode.Uri.file(novelPath), options).then(editor => console.log(editor))
	});
	// 下一页
	let next = vscode.commands.registerCommand('moyuread.nextpage', () => {
		console.log("next page")
		nextPage()
	})
	// 上一页
	let prev = vscode.commands.registerCommand('moyuread.prevpage', () => {
		console.log("previous page")
		prePage()
	})
	// 跳页
	let jump = vscode.commands.registerCommand('moyuread.jumppage', () => {
		// 调用 showInputBox 方法显示一个输入框
		// placeHolder 是输入框的占位符，显示在输入框内
		vscode.window.showInputBox({
			placeHolder: "请输入页码"
		}).then(value => {
			if (value) {
				//当用户输入完成后，.then 方法会得到输入的值 value。调用 jumpPage 函数
				jumpPage(value);
			}
		});
	});
	// 切换书籍
	let clickBar = vscode.commands.registerCommand('moyuread.clickStatusBar', () => {
		initPathAndEnv();
		const quickPickOptions = {
			placeHolder: `请在设置中设置书籍存放地址`,
			canPickMany: false // 设置为 true 允许多选
		};
		vscode.window.showQuickPick(Object.keys(env['books']), quickPickOptions).then((value) => {
			console.log(value);
			if (value && env['currentBook'] !== value) {
				changeBook(value);
			}
		});
	});
	// 切换状态栏
	let change = vscode.commands.registerCommand('moyuread.changeStatusBar', () => {
		console.log("changeBar");
		changeBarState();
	});



	// VSCode提供的一个事件，会在活动的文本编辑器发生变化时触发。
	vscode.window.onDidChangeActiveTextEditor(editor => {
		// 以下为事件处理函数，当活动的文本编辑器变化时执行
		// 打印到控制台
		console.log(editor);
		if (editor) {
			// 获取当前编辑器文档的文件路径
			const fspath = editor.document.uri.fsPath;
			//条件语句，检查当前编辑器的文件路径是否与指定的路径（'xc4210_self_test.c'）匹配。如果匹配，显示一些状态栏项，否则隐藏它们。
			if (fspath && fspath.toLowerCase() === path.join(__dirname, novel_name).toLowerCase()) {
				changeBar.text = "XXXX"
				changeBar.show()
				processBar.hide();
				prevBar.hide();
				nextBar.hide();
				jumpBar.hide();
			} else {
				changeBar.hide();
				processBar.hide();
				nextBar.hide();
				prevBar.hide();
				jumpBar.hide();
			}
		} else {
			changeBar.hide()
			processBar.hide();
			nextBar.hide();
			prevBar.hide();
			jumpBar.hide();
		}
	});
	
            // vscode.window.onDidChangeTextEditorSelection(event => {
			// 	let editor = vscode.window.activeTextEditor;
			// 	if (!editor) {
			// 		return;
			// 	}
			// 	// 获取当前编辑器文档的文件路径
			// 	const fspath = editor.document.uri.fsPath;
			// 	if (fspath && fspath.toLowerCase() !== path.join(__dirname, novel_name).toLowerCase()) {
			// 		return;
			// 	}
			
			// 	if (event.textEditor === editor) {
			// 			// 获取当前光标位置
			// 		let newPosition = editor.selection.active;
			// 		lineNumber = editor.selection.active.line - hang;
			// 		// 在这里执行你希望在光标位置变化时触发的操作
			// 		console.log('光标位置变化到行:', newPosition.line + 1, '列:', newPosition.character + 1);
			// 	}
				
            // });



	context.subscriptions.push(open);
	context.subscriptions.push(next);
	context.subscriptions.push(prev);
	context.subscriptions.push(jump);
	context.subscriptions.push(clickBar);
	context.subscriptions.push(change);
}

// This method is called when your extension is deactivated
function deactivate() {}

module.exports = {
	activate,
	deactivate
}

function init2(){
	initPathAndEnv()
	initNovelInfo()
	//initStatusBar()
	getPage()
}

function init(){
	initPathAndEnv()
	initNovelInfo()
	initStatusBar()
	getPage()
	let editor = vscode.window.activeTextEditor;
	if (editor) {
		const fspath = editor.document.uri.fsPath
		if (fspath && fspath.toLowerCase() === path.join(__dirname, 'novel.js').toLowerCase()) {
		changeBar.text = "隐藏"
		changeBar.show()
		processBar.show()
		nextBar.show()
		prevBar.show()
		jumpBar.show()
		}
	}

	
	// throw new Error(novelPath)
}


function initPathAndEnv(){
	console.log('初始化环境')
	// 展示的novel路径
	novelPath = path.join(__dirname, novel_name)
	const envPath = path.join(__dirname, "env.json")
	// 读取配置
	const envStr = fs.readFileSync(envPath).toString()
	if (envStr) {
		env = JSON.parse(envStr)
	} else {
		// 处理空字符串的情况，可能是赋予默认值或其他逻辑
		env = {}
	}
	const booksDir = path.join(books_dir)
	let books = fs.readdirSync(booksDir) // 获取book文件夹中文件
	books = books.filter(book => book.endsWith('txt')) // 获取文件中以txt结尾的文件
	books.forEach(book => {
	if (!env['books']) {
		env['books'] = {}
	} 
	else {
		Object.keys(env['books']).forEach(k => {
		if (!books.find(b => b === k)) {
			delete env['books'][k]
		}
		})
	}

	if (!env['books'][book]) {
		env['books'][book] = 1
	}
	})

	if (books.length === 0) {
		throw new Error(`没有txt格式的书籍,请在设置中存放书籍地址`)
	}
	if (!env['currentBook'] || !books.find(b => b === env['currentBook'])) {
		env['currentBook'] = books[0]
	}
}

// 获取设置参数
function get_setting_value(){
	let previousValue = read_mode;
	read_mode =  vscode.workspace.getConfiguration().get('moyuread.ReadMode', 1);
	if(read_mode === 2 && previousValue !== 2){
		hang = 100;
		const envPath = path.join(__dirname, "env.json")
		fs.writeFileSync(envPath, '{}')
	}
	else if(read_mode === 1 && previousValue !== 1) {
		hang = hang_1;
		const envPath = path.join(__dirname, "env.json")
		fs.writeFileSync(envPath, '{}')
	}
	else if(read_mode !== 1 && read_mode !== 2){
		throw new Error(`阅读模式只能选择1或2！`)
	}


	books_dir =  vscode.workspace.getConfiguration().get('moyuread.BooksPath', "");
	if (books_dir === ""){
		vscode.window.showInformationMessage(`请在设置中设置书籍存放地址`);
		books_dir = path.join(__dirname, "books")
	}

}


// 初始化小说内容
function initNovelInfo(){
	//同步读取文件内容。env['currentBook'] 包含要读取的文件名。
	var content = fs.readFileSync(path.join(books_dir, env['currentBook']))
	// 读取文件内容后，将其转换为字符串（使用 toString() 方法），然后使用 split("\n") 方法按行分割成一个包含每行内容的数组。数组的每个元素对应文件中的一行
	novelLines = content.toString().split("\n")
	//,通过将总行数（novelLines.length）除以 100 来计算总页数（假设每页包含 100 行）。
	totalPage = Math.ceil(novelLines.length / hang)
}

// 初始化状态栏
function initStatusBar(){
	// 使用模板字符串创建一个包含多个变量的消息字符串。
	const message = `${env['currentBook']}   ${env['books'][env['currentBook']]} | ${totalPage}`

	//创建一个状态栏项（StatusBarItem），并对其进行设置
	processBar = vscode.window.createStatusBarItem(vscode.StatusBarAlignment.Right);
	processBar.text = message;
	//定义状态栏项被点击时触发的命令。
	processBar.command = 'moyuread.clickStatusBar'


	// 上一页的bar
	prevBar = vscode.window.createStatusBarItem(vscode.StatusBarAlignment.Left);
	prevBar.text = "上一页";
	prevBar.command = 'moyuread.prevpage'

	
	// 下一页的bar
	nextBar = vscode.window.createStatusBarItem(vscode.StatusBarAlignment.Left);
	nextBar.text = "下一页";
	nextBar.command = 'moyuread.nextpage'
	
	jumpBar = vscode.window.createStatusBarItem(vscode.StatusBarAlignment.Left);
	jumpBar.text = "跳页";
	jumpBar.command = 'moyuread.jumppage'



	//创建一个切换状态栏
	changeBar = vscode.window.createStatusBarItem(vscode.StatusBarAlignment.Left);
	changeBar.text = "XXXX";
	//定义状态栏项被点击时触发的命令。
	changeBar.command = 'moyuread.changeStatusBar'
}

function delayedOperation() {
    console.log('这段代码会在延迟后执行');
}



function getPage(){
	// 截取页数
	const lines = novelLines.slice((env['books'][env['currentBook']] - 1) * hang, (env['books'][env['currentBook']] * hang))
	const filePath = path.join(__dirname, muban)
	// const data = fs.readFileSync(filePath, 'utf8');
	// var template = data.format(...lines)
	// fs.writeFileSync(novelPath, template)

	
	if (read_mode == 1){
		let editor = vscode.window.activeTextEditor;
		if (editor) {
			// 获取当前光标所在行号
			lineNumber = editor.selection.active.line-hang-fake_work_lines;
			//console.log(lineNumber)
				// 获取要插入的文本
			let commentedText = lines.map(line => `// ${line}`).join('\n');
			let combinedText = commentedText.replace(/\n/, `${fake_work}`);
			//combinedText = `${combinedText}${fake_work2}`;
				// 获取当前文档的内容
			const data = fs.readFileSync(filePath, 'utf8');

				// 在给定行号处插入文本
			let lines_data = data.split('\n');
			lines_data.splice(lineNumber, 0, combinedText);
			let modifiedData = lines_data.join('\n');

				// 使用 writeFileSync 覆盖原始文件

			fs.writeFileSync(novelPath, modifiedData, { flag: 'w' });

			// let position = new vscode.Position(lineNumber+2, 0);
			// let range = new vscode.Range(position, position);
			// editor.selection = new vscode.Selection(range.start, range.end);
			// editor.revealRange(range);
			
		}


		
		if (processBar) {
			processBar.text = `${env['currentBook']}   ${env['books'][env['currentBook']]} | ${totalPage}`
		}
		setTimeout(scrollToHere, 100);
		//scrollToHere()
		
	}
	else if(read_mode == 2){
		const data = fs.readFileSync(filePath, 'utf8');
		var template = data.format(...lines)
		vscode.workspace.saveAll()
		fs.writeFileSync(novelPath, template, { flag: 'w' })
	
		if (processBar) {
			processBar.text = `${env['currentBook']}   ${env['books'][env['currentBook']]} | ${totalPage}`
		}
		scrollToTop()
	}
	updateEnv()
}


// 更新用户进度
function updateEnv() {
	// 建了要写入的文件路径
	//__dirname 表示当前脚本所在的目录
	const envPath = path.join(__dirname, "env.json")
	// 将 JSON 字符串写入文件
	// JSON.stringify(env) 将 env 对象转换为对应的 JSON 格式的字符串
	fs.writeFileSync(envPath, JSON.stringify(env))
}

// 切换页后将光标定位到第一行
function scrollToTop() {
	let editor = vscode.window.activeTextEditor;
	if (editor) {
		let range = editor.document.lineAt(0).range;
		editor.selection = new vscode.Selection(range.start, range.end);
		editor.revealRange(range);
	}
}
// 切换页后将光标定位到相同位置
function scrollToHere() {
	let editor = vscode.window.activeTextEditor;
	if (editor) {
		// let range = editor.document.lineAt(0).range;
		// editor.selection = new vscode.Selection(range.start, range.end);
		// editor.revealRange(range);
		// let lineNumber = editor.selection.active.line
		// console.log(lineNumber)
		let position = new vscode.Position(lineNumber+hang+fake_work_lines, 0);
		console.log(lineNumber+hang)
		let range = new vscode.Range(position, position);
		editor.selection = new vscode.Selection(range.start, range.end);
		editor.revealRange(range);
	}
}



// 下一页
function nextPage() {
	// 获取当前活动的文本编辑器实例
    let editor = vscode.window.activeTextEditor;
    if (!editor) {
        return;
    }
	// 获取当前编辑器文档的文件路径
    const fspath = editor.document.uri.fsPath;
    if (fspath && fspath.toLowerCase() !== path.join(__dirname, novel_name).toLowerCase()) {
        return;
    }
    if (env['books'][env['currentBook']] < totalPage) {
        env['books'][env['currentBook']]++;
    }
    getPage();
}


// 下一页
function prePage() {
	// 获取当前活动的文本编辑器实例
    let editor = vscode.window.activeTextEditor;
    if (!editor) {
        return;
    }
	// 获取当前编辑器文档的文件路径
    const fspath = editor.document.uri.fsPath;
    if (fspath && fspath.toLowerCase() !== path.join(__dirname, novel_name).toLowerCase()) {
        return;
    }
    if (env['books'][env['currentBook']] > 1) {
        env['books'][env['currentBook']]--;
    }
    getPage();
}

function jumpPage(page){
	// 获取当前活动的文本编辑器实例
	let editor = vscode.window.activeTextEditor;
	if (!editor) {
		return;
	}
	// 获取当前编辑器文档的文件路径
	const fspath = editor.document.uri.fsPath;
	if (fspath && fspath.toLowerCase() !== path.join(__dirname, novel_name).toLowerCase()) {
		return;
	}
	if (isNumber(page)) {
		if (page < 1 || page > totalPage) {
			vscode.window.showWarningMessage(`页码范围1-${totalPage}`)
			return
		} else {
			env['books'][env['currentBook']] = page
			getPage()
		}
	} else {
		vscode.window.showWarningMessage(`请输入数字`)
	}
}


function isNumber(nubmer) {
	var re = /^[0-9]+.?[0-9]*$/; //判断字符串是否为数字 //判断正整数 /^[1-9]+[0-9]*]*$/ 
	if (!re.test(nubmer)) {
		return false;
	}
	return true
}


function changeBook(book){
	env['currentBook'] = book
	initNovelInfo()
	getPage()
} 



function changeBarState(){
	// 获取当前活动的文本编辑器实例
	let editor = vscode.window.activeTextEditor;
	if (!editor) {
		return;
	}
	// 获取当前编辑器文档的文件路径
	const fspath = editor.document.uri.fsPath;
	if (fspath && fspath.toLowerCase() !== path.join(__dirname, novel_name).toLowerCase()) {
		return;
	}

	if (changeBar.text == "XXXX") {
		changeBar.text = "隐藏"
		changeBar.show()
		//boolChange = 1
		processBar.show();
		prevBar.show();
		nextBar.show();
		jumpBar.show();
	}else{
		changeBar.text = "XXXX"
		//boolChange = 0
		processBar.hide();
		prevBar.hide();
		nextBar.hide();
		jumpBar.hide();
		changeBar.show()
	}
} 