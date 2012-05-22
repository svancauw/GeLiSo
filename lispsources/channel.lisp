;allow to exchange messages




(defun createSocket (ipAddress portNumber)
	;connect to a socket and return the tcp stream
	(comm:open-tcp-stream ipAddress portNumber :element-type 'base-char)
)





(defun receiveMessage (tcp_str) 
		
		(let 
			(
				;list of read character
				(charList nil)
				;temp read character
				(tempChar (stream:stream-read-char-no-hang tcp_str))
			)
		
		
		;loop to read all characters of a given message
		(loop while t do
			;check if the buffer is empty
			(if (not (equal tempChar nil))
				;then 
				(progn
					;if we have read everything
					(if (equal tempChar #\;)
						(progn
							(return)
						)
						(progn
								(setq charList (append charList (list tempChar)))
						)

					)
					
				)
			)
			
			;read next character
			(setq tempChar (stream:stream-read-char-no-hang tcp_str))
			
		)
		
		(let 
			(
				;we create a string message from the list of characters and return it
				(messageToReturn (coerce (coerce charList 'vector) 'string))
			)
			(setq messageToReturn messageToReturn)
		)
		)
)





(defun sendMessage (message tcp_str)

	
	;write the string on the buffer
	(write-string (concatenate 'string message ";") tcp_str)

	;flush the buffer data
	(force-output tcp_str)
	
)
