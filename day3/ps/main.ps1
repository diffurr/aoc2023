
function findSym([string[]]$lines, [int]$row, [int]$col, [int]$ndigs) {
    $near = "" + $lines[$row - 1].Substring($col - 1, $ndigs + 2)
    $near += $lines[$row + 1].Substring($col - 1, $ndigs + 2)
    $near += $lines[$row][$col - 1]
    $near += $lines[$row][$col + $ndigs]
    
    for ($i = 0; $i -lt $near.Length; $i += 1) {
        $ch = $near[$i]
        if (($ch -ge '!' -and $ch -le '-')`
         -or ($ch -eq '/')`
         -or ($ch -ge ':' -and $ch -le '@')) {
            return $true
         }
    }
    return $false
}

function findGear([string[]]$lines, [int]$row, [int]$col, [int]$ndigs) {
    $near = @()
    $near += $lines[$row - 1].Substring($col - 1, $ndigs + 2)
    $near += $lines[$row].Substring($col - 1, $ndigs + 2)
    $near += $lines[$row + 1].Substring($col - 1, $ndigs + 2)
    
    for ($r = 0; $r -lt $near.Length; $r += 1) {
        for ($c = 0; $c -lt $near[$r].Length; $c += 1) {
            if ($near[$r][$c] -eq '*') {
                return ([string]($row - 1 + $r) + ',' + [string]($col - 1 + $c))
            }
        }
    }
    return $null
}
function partOne([string[]]$lines) {
    $sum = 0
    for ($row = 0; $row -lt $lines.Count; $row += 1) {
        for ($col = 0; $col -lt $lines[$row].Length; $col += 1) {
            $ch = $lines[$row][$col]
            if ($ch -ge '0' -and $ch -le '9') {
                $numstr = ""
                do {
                    $numstr += $ch
                    $col += 1
                    $ch = $lines[$row][$col]
                } while ($ch -ge '0' -and $ch -le '9')
                if (findSym $lines $row ($col - $numstr.Length) $numstr.Length) {
                    $sum += [int]$numstr
                }
            }
        }
    }
    return $sum
}
function partTwo([string[]]$lines) {
    $gears = @{}
    for ($row = 0; $row -lt $lines.Count; $row += 1) {
        for ($col = 0; $col -lt $lines[$row].Length; $col += 1) {
            $ch = $lines[$row][$col]
            if ($ch -ge '0' -and $ch -le '9') {
                $numstr = ""
                do {
                    $numstr += $ch
                    $col += 1
                    $ch = $lines[$row][$col]
                } while ($ch -ge '0' -and $ch -le '9')
                $gearid = findGear $lines $row ($col - $numstr.Length) $numstr.Length
                if ($gearid) { 
                    if ($gears.ContainsKey($gearid)) {
                        $gears[$gearid] += [int]$numstr
                    } else {
                        $gears[$gearid] = @()
                        $gears[$gearid] += [int]$numstr
                    }
                }
            }
        }
    }

    $sum = 0
    foreach ($val in $gears.Values) {
        if ($val.Length -eq 2) {
            $sum += $val[0] * $val[1]
        }
    }
    return $sum
}

$in = Get-Content("..\input.txt")
$newinput = @()
$newinput += '.' * ($in[0].Length + 2)
$in | %{$newinput += '.' + $_ + '.'}
$newinput += '.' * ($in[0].Length + 2)

$time1 = Measure-Command { $res1 = partOne $newinput }
Write-Output ("part one = " + $res1)
Write-Output ("time[ms] = " + $time1.TotalMilliseconds)

$time2 = Measure-Command { $res2 = partTwo $newinput }
Write-Output ("part two = " + $res2)
Write-Output ("time[ms] = " + $time2.TotalMilliseconds)