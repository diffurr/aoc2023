function parseInput($lines) {
    $dirs = $lines[0]
    $nodes = @{}
    $lines[2..$lines.Length] | ForEach-Object {
        $nodes[$_.Substring(0, 3)] = @( $_.Substring(7, 3), $_.Substring(12, 3))
    }
    return @{ dirs = $dirs; nodes = $nodes}
}

function lcm($x, $y) {
    return ($x * $y) / [bigint]::GreatestCommonDivisor($x, $y)
}

function part1($in) {
    $currNode = "AAA"
    $idx = 0
    $step = 0
    while($true) {
        if ($currNode -eq "ZZZ") { break }
        if ($in.dirs[$idx] -eq 'L') {
            $currNode = $in.nodes[$currNode][0]
        } 
        else {
            $currNode = $in.nodes[$currNode][1]
        }
        $idx = ($idx + 1) % $in.dirs.Length
        $step += 1
    }
    return $step
}

function part2($in) {
    $nodesA = $in.nodes.Keys | Where-Object {
        $_[2] -eq 'A'
    }

    $total = 1
    $nodesA | ForEach-Object {
        $idx = 0
        $currNode = $_
        $step = 0
        while ($true) {
            if ($currNode[2] -eq 'Z') { break }
            if ($in.dirs[$idx] -eq 'L') {
                $currNode = $in.nodes[$currNode][0]
            } 
            else {
                $currNode = $in.nodes[$currNode][1]
            }
            $idx = ($idx + 1) % $in.dirs.Length
            $step += 1
        }
        $total = lcm $total $step
    }
    return $total
}

$in = parseInput (Get-Content "..\input.txt")
$time = Measure-Command { $res = part1 $in }
Write-Output ("part1 = " + $res)
Write-Output ("time[ms] = " + $time.TotalMilliseconds)
$time = Measure-Command { $res = part2 $in}
Write-Output ("part2 = " + $res)
Write-Output ("time[ms] = " + $time.TotalMilliseconds)
