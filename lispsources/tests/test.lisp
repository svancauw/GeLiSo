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
		
		;create the gecode manager and connect the sockets
		(setq gm (make-instance 'GecodeManager :sender (createSocket (first endpoint_send) (second endpoint_send)) :receiver (createSocket (first endpoint_receive) (second endpoint_receive))))
		
		(print "The Gecode Manager has been created")
					
		(sendMessage "newSpace" (getSender gm))
		(receiveMessage (getReceiver gm))
		
)

(defun test3 ()
		(setq endpoint_receive '("127.0.0.1" 2222))
		(setq endpoint_send '("127.0.0.1" 3333))
		
		;create the gecode manager and connect the sockets
		(setq gm (make-instance 'GecodeManager :sender (createSocket (first endpoint_send) (second endpoint_send)) :receiver (createSocket (first endpoint_receive) (second endpoint_receive))))
		
		(print "The Gecode Manager has been created")
					
		(setq sp (newSpace gm))
		
		(print "The space uuid is :")
		(print sp)
		
)

(defun test4 ()
		(setq endpoint_receive '("127.0.0.1" 2222))
		(setq endpoint_send '("127.0.0.1" 3333))
		
		;create the gecode manager and connect the sockets
		(setq gm (make-instance 'GecodeManager :sender (createSocket (first endpoint_send) (second endpoint_send)) :receiver (createSocket (first endpoint_receive) (second endpoint_receive))))
		
		(print "The Gecode Manager has been created")
					
		(setq sp (newSpace gm))
		
		(print "The space uuid is :")
		(print sp)
		
		(beginSearch gm)
		
)

(defun test5 ()
		(setq endpoint_receive '("127.0.0.1" 2222))
		(setq endpoint_send '("127.0.0.1" 3333))
		
		;create the gecode manager and connect the sockets
		(setq gm (make-instance 'GecodeManager :sender (createSocket (first endpoint_send) (second endpoint_send)) :receiver (createSocket (first endpoint_receive) (second endpoint_receive))))
		
		(print "The Gecode Manager has been created")
					
		(setq sp (newSpace gm))
		
		(print "The space uuid is :")
		(print sp)
		
		;(setq tu (newTuple gm '(1 2)))
		(setq tu (newTuple gm '(1 2 3 4 5)))
		
		(beginSearch gm)
		
)

(defun test6 ()
		(setq endpoint_receive '("127.0.0.1" 2222))
		(setq endpoint_send '("127.0.0.1" 3333))
		
		;create the gecode manager and connect the sockets
		(setq gm (make-instance 'GecodeManager :sender (createSocket (first endpoint_send) (second endpoint_send)) :receiver (createSocket (first endpoint_receive) (second endpoint_receive))))
		
		(print "The Gecode Manager has been created")
					
		(setq sp (newSpace gm))
		
		(print "The space uuid is :")
		(print sp)
		
		;(setq tu (newTuple gm '(1 2)))
		(setq tu (newTuple gm '(1 2 3 4 5)))
		
		(setq glb (newGRelation gm 5))
		
		(beginSearch gm)
		
)

(defun test7 ()
		(setq endpoint_receive '("127.0.0.1" 2222))
		(setq endpoint_send '("127.0.0.1" 3333))
		
		;create the gecode manager and connect the sockets
		(setq gm (make-instance 'GecodeManager :sender (createSocket (first endpoint_send) (second endpoint_send)) :receiver (createSocket (first endpoint_receive) (second endpoint_receive))))
		
		(print "The Gecode Manager has been created")
					
		(setq sp (newSpace gm))
		
		(print "The space uuid is :")
		(print sp)
		
		;(setq tu (newTuple gm '(1 2)))
		(setq tu (newTuple gm '(1 2 3 4 5)))
		
		(setq glb (newGRelation gm 5))
		
		(GRelation-AddTuple gm glb tu)
		
		(beginSearch gm)
		
)

(defun test8 ()
		(setq endpoint_receive '("127.0.0.1" 2222))
		(setq endpoint_send '("127.0.0.1" 3333))
		
		;create the gecode manager and connect the sockets
		(setq gm (make-instance 'GecodeManager :sender (createSocket (first endpoint_send) (second endpoint_send)) :receiver (createSocket (first endpoint_receive) (second endpoint_receive))))
		
		(print "The Gecode Manager has been created")
					
		(setq sp (newSpace gm))
		
		(print "The space uuid is :")
		(print sp)
		
		;(setq tu (newTuple gm '(1 2)))
		(setq tu (newTuple gm '(1 2 3 4 5)))
		
		(setq glb (newGRelation gm 5))
		(setq lub (newGRelation gm 5))
		
		(GRelation-AddTuple gm lub tu)
		
		(setq var1 (newCPRelVar gm sp glb lub))
		
		(beginSearch gm)
		
)

(defun test9 ()
		(setq endpoint_receive '("127.0.0.1" 2222))
		(setq endpoint_send '("127.0.0.1" 3333))
		
		;create the gecode manager and connect the sockets
		(setq gm (make-instance 'GecodeManager :sender (createSocket (first endpoint_send) (second endpoint_send)) :receiver (createSocket (first endpoint_receive) (second endpoint_receive))))
		
		(print "The Gecode Manager has been created")
					
		(setq sp (newSpace gm))
		
		(print "The space uuid is :")
		(print sp)
		
		;(setq tu (newTuple gm '(1 2)))
		(setq tu (newTuple gm '(1 2 3 4 5)))
		
		(setq glb (newGRelation gm 5))
		(setq lub (newGRelation gm 5))
		
		(GRelation-AddTuple gm lub tu)
		
		(setq var1 (newCPRelVar gm sp glb lub))
		
		(branch gm sp var1)
		
		(setq se (newSearchEngine gm sp 0))
		
		(setq sol1 (nextSolution gm sp se))
		
		(quitGecode gm)
		
)

(defun test10 ()
		(setq endpoint_receive '("127.0.0.1" 2222))
		(setq endpoint_send '("127.0.0.1" 3333))
		
		;create the gecode manager and connect the sockets
		(setq gm (make-instance 'GecodeManager :sender (createSocket (first endpoint_send) (second endpoint_send)) :receiver (createSocket (first endpoint_receive) (second endpoint_receive))))
		
		(print "The Gecode Manager has been created")
					
		(setq sp (newSpace gm))
		
		(print "The space uuid is :")
		(print sp)
		
		;(setq tu (newTuple gm '(1 2)))
		(setq tu (newTuple gm '(1 2 3 4 5)))
		(setq tu2 (newTuple gm '(6 7 8 9 10)))
		
		(setq glb1 (newGRelation gm 5))
		(setq lub1 (newGRelation gm 5))
		
		(GRelation-AddTuple gm lub1 tu)
		(GRelation-AddTuple gm lub1 tu2)
		
		(setq var1 (newCPRelVar gm sp glb lub))
		
		(branch gm sp var1)
		
		(setq se (newSearchEngine gm sp 0))
		
		(setq sol1 (nextSolution gm sp se))
		
		(setq sol2 (nextSolution gm sp se))
		
		(setq solRel1 (getVarInSpace gm sol1 var1))
		
		(setq solRel2 (getVarInSpace gm sol2 var1))
		
		(print "solRel1 : ")
		(print solRel1)
		(print "solRel2 : ")
		(print solRel2)
				
		(quitGecode gm)
		
)

(defun test11 ()
		(setq endpoint_receive '("127.0.0.1" 2222))
		(setq endpoint_send '("127.0.0.1" 3333))
		
		;create the gecode manager and connect the sockets
		(setq gm (make-instance 'GecodeManager :sender (createSocket (first endpoint_send) (second endpoint_send)) :receiver (createSocket (first endpoint_receive) (second endpoint_receive))))
					
		(setq sp (newSpace gm))
		
		;(setq tu (newTuple gm '(1 2)))
		(setq tu1 (newTuple gm '(1 2 3 4 5)))
		(setq tu2 (newTuple gm '(6 7 8 9 10)))
		
		(setq tu21 (newTuple gm '(1 2 3 4 5)))
		(setq tu22 (newTuple gm '(6 7 8 9 10)))
		
		(setq glb1 (newGRelation gm 5))
		(setq lub1 (newGRelation gm 5))
		
		(GRelation-AddTuple gm lub1 tu1)
		(GRelation-AddTuple gm lub1 tu2)
		
		(setq var1 (newCPRelVar gm sp glb1 lub1))
		
		(setq glb2 (newGRelation gm 5))
		(setq lub2 (newGRelation gm 5))
		
		(GRelation-AddTuple gm lub2 tu21)
		(GRelation-AddTuple gm lub2 tu22)
		
		(setq var2 (newCPRelVar gm sp glb2 lub2))
		
		(setq glb3 (newGRelation gm 5))
		(setq lub3 (newGRelation gm 5))
		
		(GRelation-AddTuple gm lub3 tu1)
		(GRelation-AddTuple gm lub3 tu2)
		
		(setq var3 (newCPRelVar gm sp glb3 lub3))
		
		;(debugSpace gm sp)
		
		(branch gm sp var1)
		
		(branch gm sp var2)
		(branch gm sp var3)
		
		(intersectConstraint gm sp var1 var2 var3)
		
		(setq se (newSearchEngine gm sp 0))
		
		(setq sol1 (nextSolution gm sp se))
		
		(setq sol2 (nextSolution gm sp se))
		
		(setq sol3 (nextSolution gm sp se))
		
		(printSpace gm sol1)
		
		(printSpace gm sol2)
		
		(printSpace gm sol3)
				
		(quitGecode gm)
		
)

(defun test12 ()
		(setq endpoint_receive '("127.0.0.1" 2222))
		(setq endpoint_send '("127.0.0.1" 3333))
		
		;create the gecode manager and connect the sockets
		(setq gm (make-instance 'GecodeManager :sender (createSocket (first endpoint_send) (second endpoint_send)) :receiver (createSocket (first endpoint_receive) (second endpoint_receive))))
					
		(setq sp (newSpace gm))
		
		;(setq tu (newTuple gm '(1 2)))
		(setq tu1 (newTuple gm '(1 2 3 4 5)))
		
		(print (getTupleArity gm tu1))
				
		(quitGecode gm)
		
)

(defun test13 ()
		(setq endpoint_receive '("127.0.0.1" 2222))
		(setq endpoint_send '("127.0.0.1" 3333))
		
		;create the gecode manager and connect the sockets
		(setq gm (make-instance 'GecodeManager :sender (createSocket (first endpoint_send) (second endpoint_send)) :receiver (createSocket (first endpoint_receive) (second endpoint_receive))))
					
		(setq sp (newSpace gm))
		
		(setq glb (newGRelation gm 3))
		(setq lubAndTuple (createBoundedFullGroundRelation gm '(0 5 6 10 11 15))) 
		(setq lub (first lubAndTuple))
		
		(print (first lubAndTuple))
		(print (second lubAndTuple))
		
		(setq var (newCPRelVar gm sp glb lub))
		
		(printSpace gm sp)
				
		(quitGecode gm)
		
)

;join constraint test
(defun test14 ()
		(setq endpoint_receive '("127.0.0.1" 2222))
		(setq endpoint_send '("127.0.0.1" 3333))
		
		;create the gecode manager and connect the sockets
		(setq gm (make-instance 'GecodeManager :sender (createSocket (first endpoint_send) (second endpoint_send)) :receiver (createSocket (first endpoint_receive) (second endpoint_receive))))
					
		(setq sp (newSpace gm))
		
		(setq grA (newGRelation gm 3))
		(setq tuA (newTuple gm '(1 2 3)))
		(GRelation-AddTuple gm grA tuA)
		
		(setq varA (newCPRelVar gm sp grA grA))
		
		(setq grB (newGRelation gm 3))
		(setq tuB1 (newTuple gm '(2 3 7)))
		(setq tuB2 (newTuple gm '(2 3 8)))
		(setq tuB3 (newTuple gm '(2 4 9)))
		(GRelation-AddTuple gm grB tuB1)
		(GRelation-AddTuple gm grB tuB2)
		(GRelation-AddTuple gm grB tuB3)
		
		(setq varB (newCPRelVar gm sp grB grB))
		
		(setq glbC (newGRelation gm 4))
		(setq lubC (newGRelation gm 4))
		
		(setq tuC1 (newTuple gm '(1 2 3 7)))
		(setq tuC2 (newTuple gm '(1 2 3 8)))
		(GRelation-AddTuple gm lubC tuC1)
		(GRelation-AddTuple gm lubC tuC2)
		
		(setq varC (newCPRelVar gm sp glbC lubC))
		
		(printSpace gm sp)
		
		(joinConstraint gm sp varA 2 varB varC)
		
		(branch gm sp varA)
		(branch gm sp varB)
		
		(setq se (newSearchEngine gm sp 0))
		
		(setq sol1 (nextSolution gm sp se))
		
		(if (string/= sol1 "0")
			(progn 
			(printSpace gm sol1)	
			)
		)
				
		(quitGecode gm)
		
)