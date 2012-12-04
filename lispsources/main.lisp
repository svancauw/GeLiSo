;load this file to test GeLiSo from Lisp (e.g., (load "/Users/saschavancauwelaert/Documents/EPL/PhD/code/GeLiSo/GeLiSo/lispsources/main.lisp"))
;currently, it must be done after having launched the C++ application of GeLiSo (i.e., build/bin/gelisoexec)
;then call (main /Path/To/GeLiSo/Dir/lispsources) where /Path/To/GeLiSo/Dir/ is the path where you have installed GeLiSo
;e.g., (main "/Users/saschavancauwelaert/Documents/EPL/PhD/code/GeLiSo/GeLiSo/lispsources/")

(defun main (lispSourceDir)
	
	;TODO : launch the C++ server (don't work well)
	;(system:run-shell-command "/Users/saschavancauwelaert/Documents/EPL/PhD/code/GeLiSo_interface/build/bin/gelisoexec")
	;(sleep 5)
	;(print "Now we begin")
	
	;go in the source directory
	;(change-directory "/Users/saschavancauwelaert/Documents/EPL/PhD/code/GeLiSo_interface/GeLiSo/lispsources/")
	;(change-directory "/Users/saschavancauwelaert/Documents/EPL/PhD/code/GeLiSo/GeLiSo/lispsources/")
	(change-directory lispSourceDir)
	
	;load the needed files
	(load "channel.lisp")
	(load "GecodeManager.lisp")
	(load "open music add-ons/CPRel_utils.lisp")
	
	;load the test file
	
	(load "tests/test.lisp")
	
	(test14)

)