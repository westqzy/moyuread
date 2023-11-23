def add_comments(file_path, num_comments):
    with open(file_path, 'r', encoding='UTF-8') as file:
        lines = file.readlines()
        
    total_lines = len(lines)
    lines_per_comment = total_lines // num_comments
    remainder = total_lines % num_comments

    new_lines = []
    for i, line in enumerate(lines):
        new_lines.append(line)
        if remainder > 0 and (i + 1) % (lines_per_comment + 1) == 0:
            comment = f'//{{{(i + 1) // (lines_per_comment + 1)-1}}}\n'
            new_lines.append(comment)
            remainder -= 1
        elif remainder == 0 and (i + 1) % lines_per_comment == 0:
            comment = f'//{{{(i + 1) // lines_per_comment-1}}}\n'
            new_lines.append(comment)


    with open(file_path, 'w',  encoding='UTF-8') as file:
        file.writelines(new_lines)

# 使用示例，假设文件名为example.c，每隔5行插入一段注释
add_comments('./muban.c', 99)