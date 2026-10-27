<?php
declare(strict_types=1);

// ============================================================
// 0. 会话与超全局兜底
// ============================================================
if (PHP_SAPI !== 'cli') {
    session_start();                    // Web 环境下启动会话
}

// 所有超全局先兜底成数组，避免 CLI / 单测环境访问时报 Warning
$_GET     = $_GET     ?? [];
$_POST    = $_POST    ?? [];
$_SERVER  = $_SERVER  ?? [];
$_COOKIE  = $_COOKIE  ?? [];
$_SESSION = $_SESSION ?? [];            // CLI 下没 session_start，也要兜底

// ============================================================
// 0.1 【新增】演示数据注入：让脚本"无论怎么跑"都能走完全流程
// ============================================================
// 目的：命令行/首次访问时 $_GET、$_POST 是空的，若保持原逻辑
//       ($id=0) 会被下面 exit() 掐断，永远看不到最后的 HTML。
// 做法：只"补默认值"，用户/浏览器真实传了就以真实值优先。
if (PHP_SAPI === 'cli' || ($_GET['id'] ?? '') === '') {
    $_GET['id']    = $_GET['id']    ?? 1;          // 合法 id，保证流程能走完
    $_POST['name'] = $_POST['name'] ?? 'Tom';      // 合法姓名，演示"正常分支"
}

// ============================================================
// 1. 取 $_GET 参数
// ============================================================
$id = (int)($_GET['id'] ?? 0);          // (int) 强转：非数字→0
if ($id <= 0) {                         // 真实请求若传 0/负数/abc → 被拒绝
    http_response_code(400);
    exit("invalid id");
}
// 正式查库必须参数化：
// $stmt = $pdo->prepare("SELECT ... WHERE id = ?");
// $stmt->execute([$id]);

// ============================================================
// 2. 取 $_POST 参数（输入阶段只校验、不转义）
// ============================================================
$rawName = $_POST['name'] ?? '';
if (!is_string($rawName)) {             // ?name[]=a 会传成数组，必须防
    $rawName = '';
}
$name = trim($rawName);
if ($name === '' || mb_strlen($name) > 50) {
    $name = '匿名';
}

// ============================================================
// 3. 输出转义（防 XSS）——这是给"HTML 输出"用的版本
// ============================================================
$safeName = htmlspecialchars($name, ENT_QUOTES | ENT_SUBSTITUTE, 'UTF-8');

// ============================================================
// 4. 会话写入
// ============================================================
$_SESSION['user'] = 'Tom';

// ============================================================
// 5. 其它超全局
// ============================================================
$ip   = $_SERVER['REMOTE_ADDR'] ?? '0.0.0.0';
$ua   = $_SERVER['HTTP_USER_AGENT'] ?? '';
$uri  = $_SERVER['REQUEST_URI'] ?? '/';

$theme = $_COOKIE['theme'] ?? 'light';
if (!in_array($theme, ['light', 'dark'], true)) {
    $theme = 'light';
}

$uploadOk = false;
if (isset($_FILES['avatar'])) {
    $f = $_FILES['avatar'];
    if (($f['error'] ?? UPLOAD_ERR_NO_FILE) === UPLOAD_ERR_OK) {
        $dest = __DIR__ . '/uploads/' . bin2hex(random_bytes(8)) . '.bin';
        $uploadOk = move_uploaded_file($f['tmp_name'], $dest);
    }
}

$GLOBALS['site'] = 'Demo';

// ============================================================
// 6. 演示输出：PHP 准备数据 → 在 HTML 模板里"填空"
// ============================================================
// 下面 `？>` 结束 PHP 代码块，进入"HTML 模板模式"。
// 这是一种"PHP 与 HTML 混写"的写法：
//   - 括号外是原样的 HTML，PHP 不解析
//  - 遇到 `<?= ... ？>` 临时切回 PHP 并把值 echo 出来
// 好处：视图层和数据准备分开，模板里只负责"展示"。
?>
<!doctype html>
<!-- ↑ HTML5 文档类型声明。放在第一行，让浏览器用标准模式渲染。
        少了它浏览器会进入"怪异模式(quirks mode)"，CSS 行为会有差异。 -->

<meta charset="utf-8">
<!-- ↑ 声明页面字符集为 UTF-8。
        必须是页面最早出现的标签之一（前 1024 字节内），
        否则浏览器可能用错误编码解析，导致中文乱码。
        注意：它只影响浏览器"怎么解码"，不改变 PHP 输出的字节。 -->

<!-- 下面 4 行是 HTML 段落。
     `<?= $x ?>` 是 `<?php echo $x; ?>` 的简写，PHP 5.4+ 都支持。
     内容经过上一步处理后拼进 HTML，输出给浏览器。 -->

<p>id: <?= $id ?></p>
<!-- ↑ $id 是 int，不含 HTML 特殊字符，直接输出是安全的 -->

<p>name: <?= $safeName ?></p>
<!-- ↑ $safeName 在 PHP 段已经 htmlspecialchars 过，
        所以即使 $name 是 "<script>alert(1)</script>"，
        浏览器只会显示成文本，不会执行脚本（防 XSS）。 -->

<p>ip: <?= htmlspecialchars($ip, ENT_QUOTES, 'UTF-8') ?></p>
<!-- ↑ $ip 来自 $_SERVER，没在前面转义过，所以此处**必须**现场转义。
        如果直接 <?= $ip ?>，攻击者可以通过伪造 UA/IP 之类注入 HTML。
        原则：凡是"没经过专门转义"的变量，输出到 HTML 前都要转义。 -->

<p>uri: <?= htmlspecialchars($uri, ENT_QUOTES, 'UTF-8') ?></p>
<!-- ↑ 同上，$uri 里可能带 ?x=<script>，必须转义 -->

<!-- ↓ 下面是新增的展示行，把原来只算不用的变量也打印出来，
       方便观察每个超全局取到了什么 -->
<p>ua: <?= htmlspecialchars($ua, ENT_QUOTES, 'UTF-8') ?></p>
<p>theme: <?= htmlspecialchars($theme, ENT_QUOTES, 'UTF-8') ?></p>
<p>session.user: <?= htmlspecialchars($_SESSION['user'], ENT_QUOTES, 'UTF-8') ?></p>
<p>site: <?= htmlspecialchars($GLOBALS['site'], ENT_QUOTES, 'UTF-8') ?></p>
<p>upload: <?= $uploadOk ? 'ok' : 'skipped' ?></p>