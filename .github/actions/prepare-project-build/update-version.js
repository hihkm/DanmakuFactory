import { readFileSync, writeFileSync } from "fs";

function updateVersionHeader(sha) {
  const headerPath = "Define/CLIDef.h";
  const shortShaVersion = `${sha.substring(0, 7)}-dev`;

  try {
    let content = readFileSync(headerPath, "utf8");

    // 匹配 #define VERSION "..."
    const versionRegex = /(^\s*#define\s+VERSION\s+["'])([^"']+)["']/m;

    if (!versionRegex.test(content)) {
      console.error(`❌ 未在 ${headerPath} 中找到 VERSION 定义`);
      process.exit(1);
    }

    const newContent = content.replace(versionRegex, `$1${shortShaVersion}"`);
    writeFileSync(headerPath, newContent, "utf8");

    console.log(
      `✅ 成功更新 ${headerPath} 中的 VERSION 为 "${shortShaVersion}"`
    );
  } catch (err) {
    if (err.code === "ENOENT") {
      console.error(`❌ 文件未找到: ${headerPath}`);
    } else {
      console.error(`❌ 更新失败:`, err.message);
    }
    process.exit(1);
  }
}

// 从环境变量或参数获取 SHA
const sha = process.env.GITHUB_SHA || process.argv[2];
if (!sha) {
  console.error("❌ 请提供 commit SHA");
  process.exit(1);
}

updateVersionHeader(sha);
