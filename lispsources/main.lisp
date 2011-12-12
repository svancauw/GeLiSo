;to use this file :
;(load "/Users/saschavancauwelaert/Documents/EPL/PhD/code/GeLiSo_interface/GeLiSo/lispsources/main.lisp")
;(main)

(defun main ()
	
	;go in the source directory
	(change-directory "/Users/saschavancauwelaert/Documents/EPL/PhD/code/GeLiSo_interface/GeLiSo/lispsources/")
	;load the needed functions
	(load "channel.lisp")

	;used endpoint
	(setq endpoint_receive '("127.0.0.1" 2222))
	(setq endpoint_send '("127.0.0.1" 3333))
	(with-open-stream 
		(tcp_str_receive (createSocket (first endpoint_receive) (second endpoint_receive)))
		
		(with-open-stream 
			(tcp_str_send (createSocket (first endpoint_send) (second endpoint_send)))

			(print "Waiting for a message")
			(receiveMessage tcp_str_receive)
			(print "Message received")
	
			(sendMessage "I send you a message !" tcp_str_send)
			
		)
	)
)	
	



		