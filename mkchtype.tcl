proc chtype {inputChar args} {
    set result [scan $inputChar %c]
    foreach elem $args {
	set result [expr $result | $elem]
    }
    return $result
}
