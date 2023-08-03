#!/bin/bash

# 遍历当前目录及子目录下的所有cpp文件
find . -type f -name "*.cpp" | while read file; do
    # 将文件名中的::替换为$$
    new_file=$(echo "$file" | sed 's/::/$$/g')
    # 如果新文件名不同于旧文件名，则重命名文件
    if [ "$new_file" != "$file" ]; then
        mv "$file" "$new_file"
        echo "Renamed: $file -> $new_file"
    fi
done

echo "替换完成。"
