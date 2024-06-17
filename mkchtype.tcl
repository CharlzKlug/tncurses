proc chtype {inputChar args} {
    set result [scan $inputChar %c]
    foreach elem $args {
	set result [expr $result | $elem]
    }
    return $result
}

proc string-to-chtypes-lst {inputString} {
    set intList {}
    for {set i 0} {$i < [string length $inputString]} {incr i} {
	set tmpVal [scan [string index $inputString $i] %c]
	lappend intList $tmpVal
    }
    return $intList
}
