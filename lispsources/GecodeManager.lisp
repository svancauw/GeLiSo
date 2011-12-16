


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
		
