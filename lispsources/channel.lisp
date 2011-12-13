;allow to exchange messages




(defun createSocket (ipAddress portNumber)
	;connect to a socket and return the tcp stream
	(comm:open-tcp-stream ipAddress portNumber :element-type 'base-char)
)





(defun receiveMessage (tcp_str) 
		
		(print "receiveMessage function : 1")
		;list of read character
		(setq charList nil)
		(print "receiveMessage function : 2")
		(setq somethingRead nil);boolean flag to know if something has already been read
		(setq tempChar (stream:stream-read-char-no-hang tcp_str))
		
		(print "receiveMessage function : 3")
		
		;loop to read all characters of a given message
		(loop while t do
			(print "receiveMessage function : 4")
			;check if there is something to read
			(if (not (equal tempChar nil))
				;then 
				(progn 
					(print "receiveMessage function : 5")
					(setq charList (append charList (list tempChar)))
					(setq somethingRead t);now we have read something so we remember it
				)
				;else
				(if somethingRead
					(progn
						(print "receiveMessage function : 6")
						(return);if something has been read and that we encounter nil, we return because the message has been completely read
					)
					(progn
						(print "receiveMessage function : What ???")
					)
					
				)
			)
			;read next character
			(setq tempChar (stream:stream-read-char-no-hang tcp_str))
			(print "receiveMessage function : 7")	
		)
		(print "receiveMessage function : 8")
		;we create a string message from the list of characters and return it
		;(setq arrayFromList (make-array (list-length charList) :initial-contents charList))
		(setq messageToReturn (coerce (coerce charList 'vector) 'string))
		(print "receiveMessage function : 9")
		(print messageToReturn)

)





(defun sendMessage (message tcp_str)
	(print "sendMessage function : we send the following message")
	(print message)
	(write-sequence message tcp_str)
	(print "The message has been sent")
)
