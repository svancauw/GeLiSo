;to use this file :
;(load "/Users/saschavancauwelaert/Documents/EPL/PhD/code/GeLiSo_interface/GeLiSo/lispsources/main.lisp")
;(main)

(defun main ()
	
	;launch the C++ server
	;(system:call-system "/Users/saschavancauwelaert/Documents/EPL/PhD/code/GeLiSo_interface/build/bin/gelisoexec" :wait t)
	
	;go in the source directory
	(change-directory "/Users/saschavancauwelaert/Documents/EPL/PhD/code/GeLiSo_interface/GeLiSo/lispsources/")
	
	;load the needed files
	(load "channel.lisp")
	(load "GecodeManager.lisp")
	
	;load the test file
	
	(load "tests/test.lisp")
	
	(test9)

)	
	



		