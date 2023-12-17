function partOne([string[]] $lines) {
    $sum = 0
    $lines | % {
        $wins = @()
        $scratch = @()
        $splits = $_.Split(':')[1].Split('|')
        ($splits[0].Split(' ') | ? { $_ -ne ""}) | % {$wins += $_}
        ($splits[1].Split(' ') | ? { $_ -ne ""}) | % {$scratch += $_}
        $intersect = @()
        $intersect += ($wins | ? {$_ -In $scratch})

        $count = $intersect.Length
        if ($count -gt 0) {
            $sum += (1 -shl ($count - 1))
        }
    }
    return $sum
}

function partTwo([string[]] $lines) {
    $lucky = @()
    $lines | %{
        $wins = @()
        $scratch = @()
        $splits = $_.Split(':')[1].Split('|')
        ($splits[0].Split(' ') | ? { $_ -ne ""}) | %{$wins += $_}
        ($splits[1].Split(' ') | ? { $_ -ne ""}) | %{$scratch += $_}
        $intersect = @()
        $intersect += ($wins | ? {$_ -In $scratch})
        $lucky += $intersect.Length
    }

    $cards = @(1) * $lucky.Length
    for ($i = 0; $i -lt $cards.Length; $i += 1) {
        for ($j = $i + 1; $j -lt $i + 1 + $lucky[$i]; $j += 1) {
            $cards[$j] += $cards[$i]
        }
    }
    $sum = 0
    $cards | % { $sum += $_}
    return $sum
}

$in = gc "..\input.txt"
$time = Measure-Command { $res = partOne $in }
echo ("part one = " + $res)
echo ("time[ms] = " + $time.TotalMilliseconds)

$time = Measure-Command { $res = partTwo $in }
echo ("part two = " + $res)
echo ("time[ms] = " + $time.TotalMilliseconds)