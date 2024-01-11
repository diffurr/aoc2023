function getInput($lines) {
    $data = @()
    $lines | ForEach-Object {
        $nums = $_.Split(' ') | ForEach-Object {
            [int]$_
        }
        $data += ,$nums
    }
    return $data
}

function allZero($nums) {
    foreach ($num in $nums) {
        if ($num -ne 0) { return $false }
    }
    return $true
}

function solution1($nums) {
    if (allZero $nums) { return 0 }
    $subs = @()
    for ($i = 1; $i -lt $nums.Length; $i += 1) {
        $subs += ($nums[$i] - $nums[$i - 1]);
    }
    return $nums[-1] + (solution1 $subs)
}

function solution2($nums) {
    if (allZero $nums) { return 0 }
    $subs = @()
    for ($i = 1; $i -lt $nums.Length; $i += 1) {
        $subs += ($nums[$i] - $nums[$i - 1]);
    }
    return $nums[0] - (solution2 $subs)
}

function part1($in) {
    return $in | 
    ForEach-Object { solution1 $_ } | 
    ForEach-Object {$sum = 0} {$sum += $_} {$sum}
}
function part2($in) {
    return $in | 
    ForEach-Object { solution2 $_ } | 
    ForEach-Object {$sum = 0} {$sum += $_} {$sum}
}
$in = getInput (Get-Content "..\input.txt")

Write-Output ("part1 = " + (part1 $in))
Write-Output ("part2 = " + (part2 $in))