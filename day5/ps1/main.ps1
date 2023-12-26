using namespace System.Collections.Generic

function readInput($lines) {
    $seeds = $lines[0].Replace("seeds: ", "").Split(' ') | % {[long]$_}
    $maps = @()
    $map = @()
    ($lines | ? { $_ -notmatch ':' })  | % {
        if ($_ -eq "") {
            if ($map.Count -gt 0) {
                $maps += ,$map
                $map = @()
            }
        } else {
            $nums = $_.Split(' ') | % {[long]$_}
            $map += @{
                start = $nums[1];
                end = $nums[1] + $nums[2] - 1;
                slide = $nums[0] - $nums[1] }
        }
    }
    $maps += ,$map
    return @{ seeds = $seeds; maps = $maps}
}

function sandFilter($maps, $range) {
    $ranges = New-Object 'Stack[Hashtable]'
    $ranges.Push($range)
    foreach ($map in $maps) {
        $newRanges = New-Object 'Stack[Hashtable]'
        while ($ranges.Count -gt 0) {
            $range = $ranges.Pop()
            $passed = $false
            foreach ($xform in $map) {
                if (($range.start -lt $xform.start) -and ($range.end -lt $xform.start)) {
                    $passed = $true
                }
                elseif (($range.start -gt $xform.end) -and ($range.end -gt $xform.end)) {
                    $passed = $true
                }
                elseif (($range.start -lt $xform.start) -and ($range.end -ge $xform.start)) {
                    $ranges.Push(@{start = $range.start; end = $xform.start - 1})
                    $newRanges.Push(@{start = $xform.start + $xform.slide; end = $range.end + $xform.slide})
                    $passed = $false
                    break
                }
                elseif (($range.start -ge $xform.start) -and ($range.end -gt $xform.end)) {
                    $ranges.Push(@{start = $xform.end + 1; end = $range.end})
                    $newRanges.Push(@{start = $range.start + $xform.slide; end = $xform.end + $xform.slide})
                    $passed = $false
                    break
                }
                else {
                    $newRanges.Push(@{ start = $range.start + $xform.slide; end = $range.end + $xform.slide})
                    $passed = $false
                    break
                }
            }
            if ($passed) {
                $newRanges.Push($range)
            }
        }
        $ranges = $newRanges
    }
    return ($ranges.values | sort)[0]
}

function sandFilterSimple($maps, $seed) {
    foreach ($map in $maps) {
        foreach ($xform in $map) {
            if (($seed -ge $xform.start) -and ($seed -le $xform.end)) {
                $seed += $xform.slide
                break
            } 
            else { continue }
            break
        }
    }
    return $seed
}

function partOne($in) {
    $min = [long]::MaxValue
    $in.seeds | % {
        $res = sandFilterSimple $in.maps $_
        $min = ($res -lt $min) ? $res : $min
    }
    return $min
}

function partTwo($in) {
    $ranges = @()
    $seeds = $in.seeds
    for ($i = 0; $i -lt $seeds.Length; $i += 2) {
        $ranges += @{
            start = $seeds[$i]; 
            end = $seeds[$i] + $seeds[$i + 1] - 1 }
    }

    $min = [long]::MaxValue
    $ranges | % {
        $res = sandFilter $in.maps $_
        $min = ($res -lt $min) ? $res : $min
    }
    return $min
}

$in = readInput (gc "..\input.txt")
$time = Measure-Command { $res = partOne $in }
echo ("part one = " + $res)
echo ("time[ms] = " + $time.TotalMilliseconds)
$time = Measure-Command { $res = partTwo $in }
echo ("part two = " + $res)
echo ("time[ms] = " + $time.TotalMilliseconds)