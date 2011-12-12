;allow to exchange messages




(defun createSocket (ipAddress portNumber)
	;connect to a socket and return the tcp stream
	(comm:open-tcp-stream ipAddress portNumber :element-type 'base-char)
)





(defun receiveMessage (tcp_str) 
		
		;list of read character
		(setq charList nil)
		
		(setq somethingRead nil);boolean flag to know if something has already been read
		(setq tempChar (stream:stream-read-char-no-hang tcp_str))
		
		;loop to read all characters of a given message
		(loop while t do
			;check if there is something to read
			(if (not (equal tempChar nil))
				;then 
				(progn 
					(setq charList (append charList (list tempChar)))
					(setq somethingRead t);now we have read something so we remember it
				)
				;else
				(if somethingRead
					(return);if something has been read and that we encounter nil, we return because the message has been completely read
				)
			)
			;read next character
			(setq tempChar (stream:stream-read-char-no-hang tcp_str))	
		)
		
		;we create a string message from the list of characters and return it
		;(setq arrayFromList (make-array (list-length charList) :initial-contents charList))
		(setq messageToReturn (coerce (coerce charList 'vector) 'string))
		(print messageToReturn)

)





(defun sendMessage (message tcp_str)
	(write-sequence message tcp_str)
)
