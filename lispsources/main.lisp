;to use this file :
;(load "/Users/saschavancauwelaert/Documents/EPL/PhD/code/GeLiSo_interface/GeLiSo/lispsources/main.lisp")
;(main)

(defun main ()
	
	;launch the C++ ser	ver (don't work well)
	;(system:run-shell-command "/Users/saschavancauwelaert/Documents/EPL/PhD/code/GeLiSo_interface/build/bin/gelisoexec")
	;(sleep 5)
	;(print "Now we begin")
	
	;go in the source directory
	(change-directory "/Users/saschavancauwelaert/Documents/EPL/PhD/code/GeLiSo_interface/GeLiSo/lispsources/")
	
	;load the needed files
	(load "channel.lisp")
	(load "GecodeManager.lisp")
	
	;load the test file
	
	(load "tests/test.lisp")
	
	(test11)

)