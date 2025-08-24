import { readFileSync, appendFileSync } from "fs";

const defaultProjectName = "DanmakuFactory";

function getProjectName() {
  try {
    const cmakeContent = readFileSync("CMakeLists.txt", "utf8");
    const match = cmakeContent.match(/project\s*\(\s*([^ )]+)/);
    return match
      ? match[1]
      : process.env.GITHUB_REPOSITORY?.split("/")?.[1] || defaultProjectName;
  } catch {
    return defaultProjectName;
  }
}

const projectName = getProjectName();

// 直接写入 GITHUB_ENV
appendFileSync(process.env.GITHUB_ENV, `PROJECT_NAME=${projectName}\n`);

console.log(`✅ Project name set to: ${projectName}`);
