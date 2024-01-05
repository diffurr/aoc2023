
$vals = @{
    '2' = 0
    '3' = 1
    '4' = 2
    '5' = 3
    '6' = 4
    '7' = 5
    '8' = 6
    '9' = 7
    'T' = 8
    'J' = 9
    'Q' = 10
    'K' = 11
    'A' = 12
}

$vals2 = @{
    'J' = 0
    '2' = 1
    '3' = 2
    '4' = 3
    '5' = 4
    '6' = 5
    '7' = 6
    '8' = 7
    '9' = 8
    'T' = 9
    'Q' = 10
    'K' = 11
    'A' = 12
}

function handStr ($_hand, $_vals) {
    $str = 0
    $str = $str -bor ($_vals['' + $_hand[0] + ''] -shl 16)
    $str = $str -bor ($_vals['' + $_hand[1] + ''] -shl 12)
    $str = $str -bor ($_vals['' + $_hand[2] + ''] -shl 8)
    $str = $str -bor ($_vals['' + $_hand[3] + ''] -shl 4)
    $str = $str -bor $_vals['' + $_hand[4] + '']
    return $str
}

function handType ($_hand) {
    $counts = @{}
    $_hand | ForEach-Object {
        $counts[$_] += 1
    }
    $sorted = ($counts.Values | Sort-Object -Descending) -join ""
    switch ($sorted){
        "5"     { return 6 }
        "41"    { return 5 }
        "32"    { return 4 }
        "311"   { return 3 }
        "221"   { return 2 }
        "2111"  { return 1 }
        "11111" { return 0 }
    }
}

function handType2 ($_hand) {
    if ($_hand -notcontains 'J') {
        return (handType $_hand)
    }
    $max = -1
    $vals2[1..$vals.Length] | ForEach-Object {
        $type = handType ($_hand -replace 'J',$_)
        if ($type -gt $max) {
            $max = $type
        }
    }
    return $max
}

function parseInput($lines){
    $hands = @()
    $lines | ForEach-Object {
        $hand = $_[0..4]
        $bid = [int]$_.Substring(6)
        $hands += ,((handStr $hand $vals), (handType $hand), $bid)
    }    
    return $hands
}

function parseInput2($lines){
    $hands = @()
    $lines | ForEach-Object {
        $hand = $_[0..4]
        $bid = [int]$_.Substring(6)
        $hands += ,((handStr $hand $vals2), (handType2 $hand), $bid)
    }    
    return $hands
}

function solution($hands) {
    $final = $hands | Sort-Object -Stable {$_[0]} | Sort-Object -Stable {$_[1]}
    $idx = 1
    $sum = 0
    $final | ForEach-Object {
        $sum += $_[2] * ($idx)
        $idx += 1
    }
    return $sum
}

function part1($lines) {
    return solution (parseInput $lines)
}

function part2($lines) {
    return solution (parseInput2 $lines)
}

$lines = (Get-Content "..\input.txt")

$time = Measure-Command { $res = part1 $lines }
Write-Output ("part1 = " + $res)
Write-Output ("time[ms] = " + $time.TotalMilliseconds)
$time = Measure-Command { $res = part2 $lines }
Write-Output ("part2 = " + $res)
Write-Output ("time[ms] = " + $time.TotalMilliseconds)