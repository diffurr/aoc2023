function getInput($lines) {
    $vflag = @($true) * $lines[0].Length
    $hflag = @()
    $lines | ForEach-Object {
        $empty = $true
        for ($i = 0; $i -lt $_.Length; $i += 1) {
            if ($_[$i] -eq '#') {
                $vflag[$i] = $false
                $empty = $false
            }
        }
        if ($empty) { $hflag += $true }
        else { $hflag += $false }
    }
    return @{
        vflag = $vflag
        hflag = $hflag
    }
}

function path($lines, $vflag, $hflag, $scale) {
    $planets = New-Object "System.Collections.Stack"
    $maxh = 0
    for ($h = 0; $h -lt $lines.Length; $h += 1) {
        $maxw = 0
        $line = $lines[$h]
        for ($i = 0; $i -lt $line.Length; $i += 1) {
            if ($vflag[$i]) {
                $maxw += $scale
            }
            else {
                if ($line[$i] -eq '#') {
                    $planets.Push(@{
                        x = $maxw
                        y = $maxh
                    })
                }
                $maxw += 1
            }
        }
        if ($hflag[$h]) { $maxh += $scale }
        else { $maxh += 1 }
    }
    $sum = 0
    while ($planets.Count -gt 0) {
        $p1 = $planets.Pop();
        foreach($p2 in $planets) {
            $sum += [math]::abs($p2.x - $p1.x) + [math]::abs($p2.y - $p1.y)
        }
    }
    return $sum
}

function solution($lines) {
    $in = getInput $lines
    $part1 = path $lines $in.vflag $in.hflag 2
    $part2 = path $lines $in.vflag $in.hflag 1000000
    return @{
        part1 = $part1
        part2 = $part2
    }
}

$lines = Get-Content "..\input.txt"
$result = solution $lines
Write-Output ("part1 = " + $result.part1)
Write-Output ("part2 = " + $result.part2)