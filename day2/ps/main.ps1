function playGame([string]$line) {
    $splits = $line.Split(':')
    $id = [int]$splits[0].Split(' ')[1]
    foreach ($sets in $splits[1].Split(';')) {
        $red = $green = $blue = 0
        foreach ($elem in $sets.Split(',')) {
            $elem = $elem.Split(' ')
            $val = [int]$elem[1]
            switch ($elem[2])
            {
               "red" {$red += $val; Break} 
               "green" {$green += $val; Break}
               "blue" {$blue += $val; Break}
            }
        }
        if ( ($red -gt 12) -or ($green -gt 13) -or ($blue -gt 14) ) {
            return 0
        }
    }
    return $id
}

function powerGame([string]$line) {
    $red = $green = $blue = 1
    $splits = $line.Split(':')
    foreach ($sets in $splits[1].Split(';')) {
        foreach ($elem in $sets.Split(',')) {
            $elem = $elem.Split(' ')
            $val = [int]$elem[1]
            switch ($elem[2])
            {
               "red" {$red = ($val -gt $red) ? $val : $red; Break} 
               "green" {$green = ($val -gt $green) ? $val : $green; Break}
               "blue" {$blue = ($val -gt $blue) ? $val : $blue; Break}
            }
        }
    }
    return $red * $green * $blue
}

$input = Get-Content("..\input.txt")

#Part One
$sum1 = 0
$input | %{$sum1 += playGame($_)}
Write-Output ("part one = " + $sum1)

#Part Two
$sum2 = 0
$input | %{$sum2 += powerGame($_)}
Write-Output ("part two = " + $sum2)