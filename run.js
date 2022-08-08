const data = require("fs").readFileSync("output").toString();

const child = require("child_process").spawn("python", ["main.py", "-l"]);

child.stdin.setEncoding("utf-8");
child.stdout.pipe(process.stdout);
child.stdin.write(data.trim() + "\n");
child.stdin.end();
