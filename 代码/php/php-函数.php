<?php
declare(strict_types=1);// 严格类型模式：类型不匹配直接抛 TypeError
                        // 若删除此行（默认弱模式），会尝试自动转换

// 1. 普通函数 + 默认参数

// 规则：默认参数必须放在参数列表最后；否则后续参数也必须给默认值
// 默认值必须是"常量表达式"（不能是函数调用或变量，PHP 8.1 起允许 new）
function add($a = 0, $b = 10) {
    return $a + $b;               // return 立即结束函数并返回值
}
echo add(5), PHP_EOL;             // 15   $b 用默认值 10
echo add(5, 20), PHP_EOL;         // 25   显式传入 $b
// echo add(5, 20, 30);           // 报错：参数过多（非可变参数时）

// 2. 可变参数（PHP 5.6+）
// ...$nums 会把"剩余所有参数"收成一个数组 $nums
// 规则：可变参数必须是"最后一个"形参
// 可配合类型声明：int ...$nums（每个元素都会被检查为 int）
function sum(int ...$nums): int {
    return array_sum($nums);      // array_sum 求数字数组之和，空数组返回 0
}
echo sum(1, 2, 3), PHP_EOL;       // 6
echo sum(), PHP_EOL;              // 0   允许不传参
echo sum(...[1, 2, 3, 4]), PHP_EOL; // 10  展开运算符：把数组"打散"成多个参数
// sum(1, "2");                   // 严格模式下抛 TypeError（弱模式下会转成 2）

// 补充：形参中 ... 还能与其他普通参数混用（放最后）
function tag(string $name, string ...$attrs): string {
    $attr = implode(" ", $attrs);  // 把属性数组拼成一段字符串
    return $attr === "" ? "<$name>" : "<$name $attr>";
}
echo tag("br"), PHP_EOL;          // <br>
echo tag("a", "href='x'"), PHP_EOL; // <a href='x'>

// 3. 类型声明（PHP 7+）
// 形参类型：string/int/float/bool/array/iterable/object/callable/类名/接口名
// 返回类型：同上 + void（无返回）/never（不返回）等
function greet(string $name): string {
    return "Hello, $name";
}
echo greet("Tom"), PHP_EOL; // Hello, Tom
echo greet("世界"), PHP_EOL;// 中文按 UTF-8 字节处理，没问题
// greet(123);              // 严格模式：TypeError
                            // 弱模式（去掉 declare）：123 会自动转成 "123"

// 联合类型（PHP 8.0+）：int|string 二选一
function showId(int|string $id): string {
    return "id=$id";
}
echo showId(1), PHP_EOL;           // id=1
echo showId("A1"), PHP_EOL;        // id=A1

// 可空类型：?string 等价于 string|null
function hi(?string $name): string {
    return $name === null ? "Hi, guest" : "Hi, $name";
}
echo hi(null), PHP_EOL;            // Hi, guest
echo hi("Tom"), PHP_EOL;           // Hi, Tom

// void：函数不返回任何值（return 后不能跟值）
function logMsg(string $msg): void {
    echo "[LOG] $msg", PHP_EOL;
}
logMsg("start");                    // [LOG] start

// 4. 匿名函数 / 闭包
// 匿名函数是一个"值"，可以赋给变量、作为参数传递
// 注意：语句结尾必须带分号 `;`
$fn = function ($x) {
    return $x * 2;
};
echo $fn(5), PHP_EOL;               // 10

// 未指定类型的闭包变量，PHP 会当"可变函数/闭包"处理

// 5. 箭头函数（PHP 7.4+）
// 语法：fn(参数) => 表达式;
// 特点：
//   1) 只能写"单个表达式"，自动作为返回值（不能写 return / 语句）
//   2) 自动按值捕获外层变量，无需 use
//   3) 需要多行逻辑时，请用 function 闭包
$double = fn($x) => $x * 2;
echo $double(5), PHP_EOL;           // 10

$prefix = "ID:";
$fmt = fn($x) => $prefix . $x;      // 自动捕获 $prefix（按值）
echo $fmt(7), PHP_EOL;              // ID:7

// 箭头函数里想"多行"只能用三元/嵌套表达式，可读性会变差，此时用 function

// 6. use 引入外部变量（闭包捕获）
// 默认按值捕获：闭包内改副本，不影响外部变量
// 想改外部变量必须写成 use (&$factor)
$factor = 3;
$mul = function ($x) use ($factor) {
    return $x * $factor;
};
echo $mul(4), PHP_EOL;              // 12

// 按引用捕获演示
$count = 0;
$inc = function () use (&$count) {
    $count++;
};
$inc();
$inc();
echo $count, PHP_EOL;               // 2   外部变量真的被改了

// 对比：箭头函数无法按引用捕获（隐式按值），需要引用时请用 function + use (&$x)

// 7. 补充高频用法（原代码没涉及但很常用）

// (1) 引用传参：函数内改形参 = 改外部变量
function addOne(array &$arr): void {
    $arr[] = "new";                 // 因为按引用传参，外部数组会被改
}
$data = [1, 2];
addOne($data);
print_r($data);                     // [1, 2, new]

// (2) 静态变量：函数内的"记忆"，跨多次调用保留
function counter(): int {
    static $n = 0;                  // 只在第一次调用时初始化一次
    return ++$n;
}
echo counter(), counter(), counter(), PHP_EOL; // 123

// (3) 全局变量：函数内默认看不到全局变量，需 global（或用 $GLOBALS）
$g = "G";
function useGlobal(): string {
    global $g;                      // 声明使用全局 $g（等价于 $g = &$GLOBALS["g"]）
    return $g;
}
echo useGlobal(), PHP_EOL;          // G

// (4) 命名参数（PHP 8.0+）：按名字传参，跳过默认值、顺序可变
function makeUser(string $name, int $age = 18, string $city = "未知"): string {
    return "$name/$age/$city";
}
echo makeUser(name: "Tom", city: "北京"), PHP_EOL; // Tom/18/北京
// 命名参数后不能再跟位置参数（会报错）

// (5) 可变函数：变量里存函数名字符串，加括号调用
$funcName = "greet";
echo $funcName("Bob"), PHP_EOL;     // Hello, Bob
// 也可结合 callable 类型：function run(callable $f) { return $f(); }

// (6) 返回引用（较少用，仅当确需"返回一个变量的引用"时）
function &getRef(array &$arr, int $i) {
    return $arr[$i];                // 返回引用，外部可改原数组元素
}
$nums = [10, 20];
$r = &getRef($nums, 1);
$r = 99;
print_r($nums);                     // [10, 99]
?>