


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
		
	(sendMessage "newSpace" (getSender gm))
			
	;wait for the answer (the uuid)
	(setq newSpaceUUID (receiveMessage (getReceiver gm)))
	
  	;return the uuid to be able to access the space
	(setq newSpaceUUID newSpaceUUID)
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
		
	(sendMessage (concatenate 'string "newTuple" " " componentString) (getSender gm))
			
	;wait for the answer
	(setq ack (receiveMessage (getReceiver gm)))
	
  	;return the uuid to be able to access the tuple
	(setq ack ack)
)		

;create a new (empty) ground relation
;arity is an integer specifying the arity of the new (empty) ground relation
(defmethod newGRelation ((gm GecodeManager) arity)
	
	;send the message
		
	(sendMessage (concatenate 'string "newGRelation" " " (write-to-string arity)) (getSender gm))
			
	;wait for the answer
	(setq ack (receiveMessage (getReceiver gm)))
	
  	;return the uuid to be able to access the ground relation
	(setq ack ack)
)

;add the tuple tu to the ground relation gr
;gr and tu are strings representing the uuid of the objects on the C++ side
(defmethod GRelation-AddTuple ((gm GecodeManager) gr tu)
	
	;send the message
		
	(sendMessage (concatenate 'string "GRelation-AddTuple" " " gr " " tu) (getSender gm))
			
	;wait for the answer
	(setq ack (receiveMessage (getReceiver gm)))
	
  	;return the ack
	(setq ack ack)
)	

;create a new CPRel variable with glb and lub as domain bounds
(defmethod newCPRelVar ((gm GecodeManager) sp glb lub)
	
	;send the message	
	(sendMessage (concatenate 'string "newCPRelVar" " " sp " " glb " " lub) (getSender gm))
			
	;wait for the answer
	(setq ack (receiveMessage (getReceiver gm)))
	
  	;return the uuid to be able to access the cprelvar
	(setq ack ack)
)

(defmethod branch ((gm GecodeManager) sp cprelvar)
	
	;send the message	
	(sendMessage (concatenate 'string "branch" " " sp " " cprelvar) (getSender gm))
			
	;wait for the answer
	(setq ack (receiveMessage (getReceiver gm)))
	
  	;return the ack
	(setq ack ack)
)	

;create a search engine
;strategyID is an id used to identify the strategy to be used in Gecode 
;0 = dfs
;1 = bab
;2 = restart
(defmethod newSearchEngine ((gm GecodeManager) sp strategyID)

	;send the (translated) message
			
	(sendMessage (concatenate 'string "newSearchEngine" " " sp " " (write-to-string strategyID)) (getSender gm))
			
	;wait for the answer
	(setq ack (receiveMessage (getReceiver gm)))
	
  	;return the ack (actual solution)
	(setq ack ack)
)

;find the next solution for a given space sp and search engine se
;it returns a solution space
(defmethod nextSolution ((gm GecodeManager) sp se)

	;send the (translated) message
		
	(sendMessage (concatenate 'string "nextSolution" " " sp " " se) (getSender gm))
			
	;wait for the answer
	(setq ack (receiveMessage (getReceiver gm)))
	
  	;return the ack (actual solution)
	(setq ack ack)
)

(defmethod quitGecode ((gm GecodeManager))

	;send the (translated) message
		
	(print "We will quit")	
	(sendMessage "quitGecode" (getSender gm))
			
	;wait for the answer
	(setq ack (receiveMessage (getReceiver gm)))
	
  	;return the ack (actual solution)
	(setq ack ack)
)

;get a relation variable on a given space (for instance solution space) as a list of list (ie a list of tuples)
(defmethod getVarInSpace ((gm GecodeManager) sp cprelvar)

	;send the (translated) message
		
	(sendMessage (concatenate 'string "getVarInSpace" " " sp " " cprelvar) (getSender gm))
			
	;wait for the answer (the actual list of list but as a string)
	(setq ack (receiveMessage (getReceiver gm)))
	
	;transform the string in a list of list (actually a list of tuple, ie the relation)
	(print (concatenate 'string "The relation as a string is : " ack))
	
	(setq splittedRel (split-sequence "-" ack :coalesce-separators t))
	
	(setq relAsList nil);list of list to be returned
	
	(loop while (first splittedRel) do ;while the list is not empty
		
		(setq tempTuple nil);the current tuple
		
		;tuple splitted as a list of integer
		(setq splittedTuple (split-sequence "[,]" (first splittedRel) :coalesce-separators t))
		
		;fill the list with the element of the list of string		
		(loop while (first splittedTuple) do
			
			;we add the next element
			(setq tempTuple (append (list (parse-integer (first splittedTuple))) tempTuple))
			
			;next element	
			(setq splittedTuple (rest splittedTuple))
		)	
		
		;we add the next tuple
		(setq relAsList (append (list tempTuple) relAsList))
		
		;next element	
		(setq splittedRel (rest splittedRel))
	)
	
  	;return the relation as list of list
	(print relAsList)
	(setq relAsList relAsList)
)
