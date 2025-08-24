#!/bin/bash
set -euo pipefail

SOURCE_DIR="$1"
OUTPUT_DIR="$2"

echo "🔍 准备发布资产：从 $SOURCE_DIR 到 $OUTPUT_DIR"

# 创建目标目录
mkdir -p "$OUTPUT_DIR"

# 遍历所有 package-* 目录
for package_dir in $SOURCE_DIR/package-*; do
    echo -e "\nProcessing $package_dir ..."

    # 跳过不存在的匹配
    [ -d "$package_dir" ] || continue

    # 从目录名提取平台和架构 (格式: package-<platform>-<arch>)
    package_name=$(basename "$package_dir")
    platform_arch="${package_name#package-}" # 去掉 package- 前缀

    # 分割平台和架构 (处理可能的多段架构名，如 "macOS-Intel")
    IFS='-' read -ra parts <<<"$platform_arch"
    platform="${parts[0]}"
    arch="${parts[@]:1}" # 处理可能有多个连字符的情况

    # 确定源文件路径，只取第一个文件
    src_file=$(find "$package_dir" -type f -print -quit)

    # 跳过不存在的文件
    [ -f "$src_file" ] || {
        echo "⚠️ 跳过: $package_dir (文件不存在)"
        continue
    }

    filename=$(basename "$src_file")
    filename="${filename%.exe}" # 去掉 .exe 后缀（如果有的话）

    # 构建目标文件名 (替换空格为连字符，确保文件名合法)
    clean_arch=$(echo "$arch" | tr ' ' '-')
    dest_filename="$OUTPUT_DIR/$filename-dev-${platform}-${clean_arch}-CLI"

    docs_dir=$(realpath docs/)

    if [ "$platform" = "Windows" ]; then
        dest_file="$dest_filename.zip"
        zip -j9 $dest_file $src_file $docs_dir/*
    else
        parent=$(dirname "$src_file")
        base=$(basename "$src_file")

        dest_file="$dest_filename.tar.gz"
        GZIP=-9 tar -czvf $dest_file -C "$parent" "$base" -C $docs_dir .
    fi

    echo "✅ $src_file → $dest_file"
done

# 验证结果
echo -e "\nAll done. Files are in '$OUTPUT_DIR':"
ls -rtlh "$OUTPUT_DIR/"

if [ "$(ls -A $OUTPUT_DIR)" ]; then
    echo "✅ 发布资产准备完成。"
else
    echo "❌ 错误: 未找到任何发布资产！"
    exit 1
fi
