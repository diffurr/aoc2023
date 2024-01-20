enum Dir { 
    N 
    E 
    S 
    W 
    X 
}

$dirs = (0, -1), (1, 0), (0, 1), (-1, 0)
$tiles = @{
    '|' = "NXSX";
    '-' = "XEXW";
    'L' = "XXEN";
    'J' = "XNWX";
    '7' = "WSXX";
    'F' = "EXXS";
    'S' = "NESW";
    '.' = "XXXX"
}

function makeMap($w, $h, $init){
    return 0..($h - 1) | ForEach-Object {
        ,([char[]]@($init) * $w)
    }
}

function closeLoop($firstd, $lastd) {
    foreach ($h in $tiles.GetEnumerator()) {
        if ($h.Key -eq 'S') { continue }
        if ([Dir]::Parse([Dir], $h.Value[$lastd.value__]) -eq $firstd) {
            return $h.Key
        }
    }
}

function follow($map, $x, $y, $dir) {
    $dist = 0
    $firstd = $dir
    $loopMap = makeMap $map[0].Length $map.Length '0'
    while ($true) {
        $nx = $x + $dirs[$dir.value__][0]
        $ny = $y + $dirs[$dir.value__][1]
        $loopMap[$y][$x] = $map[$y][$x]
        $ndir = [Dir]::Parse([Dir], $tiles["" + $map[$ny][$nx]][$dir.value__])
        if ($ndir -ne [Dir]::X) {
            $x = $nx
            $y = $ny
            $dist += 1
            if ($map[$y][$x] -eq 'S') {
                $loopMap[$y][$x] = closeLoop $firstd $dir
                return ($dist / 2), $loopMap
            }
            $dir = $ndir
        }
        else {
            return -1, $loopMap
        }
    }
}

function countInside($map) {
    $count = 0
    foreach ($row in $map) {
        $inside = $false
        $prev = '0'
        foreach ($ch in $row) {
            if ($ch -eq '|') {$inside = -not $inside}
            elseif ($ch -eq 'J' -and $prev -eq 'F') {$inside = -not $inside}
            elseif ($ch -eq '7' -and $prev -eq 'L') {$inside = -not $inside}
            elseif ($inside -and $ch -eq '0') { $count += 1}
            if ($ch -ne '-') {
                $prev = $ch
            }
        }
    }
    return $count
}

function findStart($map) {
    $rown = 0
    foreach ($row in $map) {
        $col = $row.IndexOf('S')
        if ($col -ge 0) {
            return $col, $rown
        }
        $rown += 1
    }
}

function loop($map) {
    $x, $y = findStart $map
    foreach ($dir in [Enum]::GetValues([Dir])) {
        $dist, $LoopMap = follow $map $x $y $dir
        if ($dist -ge 0) {
            return $dist, $loopMap
        }
    }
}

function solution($map) {
    $dist, $loopMap = loop $map
    $inside = countInside $loopMap
    return $dist, $inside
}

$part1, $part2 = solution (Get-Content "..\input.txt")
Write-Output ("part1 = " + $part1)
Write-Output ("part2 = " + $part2)