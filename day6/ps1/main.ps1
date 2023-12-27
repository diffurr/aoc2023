#algebraic solution from reddit u/themanushiya

function line2nums($line) {
    return $line.Split(':')[1].Trim().Split(' ') | ? {
        $_.Length -gt 0 } | % { [int]$_ } 
}

function line2num($line) {
    return [Int64]($line.Split(':')[1].Trim().Split(' ') | ? {
        $_.Length -gt 0 } | % { $s = "" } { $s += $_} { $s })
}

function part1($lines) {
    $tnums = line2nums $lines[0]
    $dnums = line2nums $lines[1]
    
    $res = 1
    0..($tnums.Length - 1) | % {
        $t = $tnums[$_]
        $d = $dnums[$_]
        $low = ($t - [Math]::Sqrt(($t * $t) - 4 * $d)) / 2
        $low = ($low % 1) ? [Math]::Ceiling($low) : $low + 1
        $top = ($t + [Math]::Sqrt(($t * $t) - 4 * $d)) / 2
        $top = ($top % 1) ? [Math]::Floor($top) : $top - 1
        $res *= $top - $low + 1
    }
    return $res
}

function part2($lines) {
    $t = line2num $lines[0]
    $d = line2num $lines[1]
    $low = ($t - [Math]::Sqrt(($t * $t) - 4 * $d)) / 2
    $low = ($low % 1) ? [Math]::Ceiling($low) : $low + 1
    $top = ($t + [Math]::Sqrt(($t * $t) - 4 * $d)) / 2
    $top = ($top % 1) ? [Math]::Floor($top) : $top - 1
    return $top - $low + 1
}

$lines = Get-Content "..\input.txt"
$time = Measure-Command { $res = part1 $lines }
echo ("part1 = " + $res)
echo ("time[ms] = " + $time.TotalMilliseconds)
$time = Measure-Command { $res = part2 $lines }
echo ("part2 = " + $res)
echo ("time[ms] = " + $time.TotalMilliseconds)