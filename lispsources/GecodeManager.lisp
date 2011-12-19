


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;class allowing to use Gecode from Common Lisp;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defclass GecodeManager ()
	;instance variables

	(
	; - variable map (a common lisp hashtable, that will contain pairs of the form <variable,uuid>)
	;(varmap :accessor getVarMap
	;		 :initform (make-hash-table);we create a new hash table for the map when creating a new GeLiSo object
	 ;        :initarg :varmap)
	
	; - sending socket
	(sender :accessor getSender
	        :initarg :sender)
	
	; - receiving socket
	(receiver :accessor getReceiver
	        :initarg :receiver)	
	)
)
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;define the different methods of the GeLiSo class;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;create a new Gecode space
(defmethod newSpace ((gm GecodeManager))
  (print "We create a new Gecode space")
  
	;(maybe later) translate the message 

	;send the (translated) message
		
	(print "We send a message for a new space")	
	(sendMessage "newSpace" (getSender gm))
	(print "Message sent !")
			
	;wait for the answer (the uuid)
	(print "Waiting for the answer (the uuid)")
	(setq newSpaceUUID (receiveMessage (getReceiver gm)))
	(print "Message received")
	
  	;return the uuid to be able to access the space
	(setq newSpaceUUID newSpaceUUID)
)

;begin the search
(defmethod beginSearch ((gm GecodeManager))
  (print "We will begin the search")
  
	;(maybe later) translate the message 

	;send the (translated) message
		
	(print "We send a message to begin the search")	
	(sendMessage "search" (getSender gm))
	(print "Message sent !")
			
	;wait for the answer
	(print "Waiting for the answer")
	(setq ack (receiveMessage (getReceiver gm)))
	(print "Message received")
	
  	;return the uuid to be able to access the space
	(setq ack ack)
)


;create a new Tuple
;componentList is a list that contains the integer component of the tuple
(defmethod newTuple ((gm GecodeManager) componentList)

	;list of integer component as a string
	(setq componentString (write-to-string (first componentList))) ;first element is put into
		
	;fill the string with all the components
	(setq componentList (rest componentList))	
	(loop while (first componentList) do ;while the list is not empty
		
		;we add the next component
		(setq componentString (concatenate 'string componentString " " (write-to-string (first componentList))))
		
		;next element	
		(setq componentList (rest componentList))
	)
	
	;send the message
		
	(print "We send a message for a new tuple")	
	(sendMessage (concatenate 'string "newTuple" " " componentString) (getSender gm))
	(print "Message sent !")
			
	;wait for the answer
	(print "Waiting for the answer")
	(setq ack (receiveMessage (getReceiver gm)))
	(print "Message received")
	
  	;return the uuid to be able to access the space
	(setq ack ack)
)		

;create a new (empty) ground relation
;arity is an integer specifying the arity of the new (empty) ground relation
(defmethod newGRelation ((gm GecodeManager) arity)
	
	;send the message
		
	(print "We send a message for a new ground relation")	
	(sendMessage (concatenate 'string "newGRelation" " " (write-to-string arity)) (getSender gm))
	(print "Message sent !")
			
	;wait for the answer
	(print "Waiting for the answer")
	(setq ack (receiveMessage (getReceiver gm)))
	(print "Message received")
	
  	;return the uuid to be able to access the space
	(setq ack ack)
)		
