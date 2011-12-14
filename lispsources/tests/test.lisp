(defun test1 ()
		;used endpoint
		(setq endpoint_receive '("127.0.0.1" 2222))
		(setq endpoint_send '("127.0.0.1" 3333))
		(with-open-stream 
		
		(tcp_str_receive (createSocket (first endpoint_receive) (second endpoint_receive)))	
			
			(with-open-stream 
				
				(tcp_str_send (createSocket (first endpoint_send) (second endpoint_send)))				
				
				(sendMessage "I send you a message !" tcp_str_send)
				
				(print "Waiting for a message")
				(receiveMessage tcp_str_receive)
				(print "Message received")
		
				
	
			)
		)
)

(defun test1bis ()
		;used endpoint
		(setq endpoint_receive '("127.0.0.1" 2222))
		(setq endpoint_send '("127.0.0.1" 3333))
		(with-open-stream 
		
		(tcp_str_send (createSocket (first endpoint_send) (second endpoint_send)))	
			
			(sendMessage "I send you a message !" tcp_str_send)
			
		)
		
		(with-open-stream 
			
			(tcp_str_receive (createSocket (first endpoint_receive) (second endpoint_receive)))
			
			(print "Waiting for a message")
			(receiveMessage tcp_str_receive)
			(print "Message received")
	
			

		)
		
)


(defun test1bisbis ()
		;used endpoint
		(setq endpoint_receive '("127.0.0.1" 2222))
		(setq endpoint_send '("127.0.0.1" 3333))
		
		
		(setq tcp_str_send (createSocket (first endpoint_send) (second endpoint_send)))	
		
		(sendMessage "I send you a message !" tcp_str_send)
		
		(close tcp_str_send)
		
		(setq tcp_str_receive (createSocket (first endpoint_receive) (second endpoint_receive)))
			
		
			
		
		
		
			
		
			
			(print "Waiting for a message")
			(receiveMessage tcp_str_receive)
			(print "Message received")
	
			

		
		
)

(defun test1bisbisbis ()
		;used endpoint
		(setq endpoint_receive '("127.0.0.1" 2222))
		(setq endpoint_send '("127.0.0.1" 3333))
		
		
		(setq tcp_str_receive (createSocket (first endpoint_receive) (second endpoint_receive)))
		(setq tcp_str_send (createSocket (first endpoint_send) (second endpoint_send)))	
		
		(sendMessage "I send you a message !" tcp_str_send)
		
		
		(print "Waiting for a message")
		(receiveMessage tcp_str_receive)
		(print "Message received")
		
		
		(sendMessage "I send you a second message !" tcp_str_send)
		
		
		(print "Waiting for a message")
		(receiveMessage tcp_str_receive)
		(print "Message received")
		
		
)



(defun test2 ()
		(setq endpoint_receive '("127.0.0.1" 2222))
		(setq endpoint_send '("127.0.0.1" 3333))
		
		;create the gecode mannager
		(setq gm (make-instance 'GecodeManager))
		
		(print "The Gecode Manager has been created")
		
		
		
		;connect to the C++ sockets
		(with-open-stream 
		(tcp_str_receive (createSocket (first endpoint_receive) (second endpoint_receive)))
			
			(with-open-stream 
				(tcp_str_send (createSocket (first endpoint_send) (second endpoint_send)))
				
				;update the sockets in the Gecode manager
				;(setf (getSender gm) tcp_str_send)
				;(setf (getReceiver gm) tcp_str_receive)
			
				
				(sendMessage "newSpace" (getSender gm))
			
			
				
				;(print "We create a space from Lisp")
				;(newSpace gm)
				;(print "The space has been created")
				
	
			)
		)
		
		
		
		
		
		
	
)