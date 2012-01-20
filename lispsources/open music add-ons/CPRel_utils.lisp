
;get a list of lists of parameters from a score represented by a list of tuples (actually represented by lists)
(defun getScoreParamFromSol (scoreRelation)
	
	;list that will be return
	(setq listOfScoreParamList nil)
	
	;get the arity of the score relation
	(setq arity (length (first scoreRelation)))
	
	;loop on all components
	(loop for tempComp from 0 to (- arity 1) do
		
		;temp scoreRelation
		(setq tempScoreRelation scoreRelation)
		
		;list that will contain all elements of the tuples, for the current component
		(setq compParamList nil)
		
		;while there are tuples
		(loop while (first tempScoreRelation) do
		            
			;get the current tuple
			(setq tempTuple (first tempScoreRelation))
			
			;add the value to the list
			(setq compParamList (cons (nth tempComp tempTuple) compParamList))
			
			;next tuple
			(setq tempScoreRelation (cdr tempScoreRelation))
		)
		
		;add the list of parameters to the list of lists
		(setq listOfScoreParamList (cons compParamList listOfScoreParamList))
		
	)
	
	;return the list of list of parameters (renversed)
	(reverse listOfScoreParamList)
	
)


;create a list of tuples from three lists of parameters of a partition (use of ternary relations)
;pre : lists must be the same size
(defun getTuplesFromScoreParam (paramList)

	;get the lists of parameters
	(setq pitchList (car paramList))
	(setq onsetList (car (cdr paramList)))
	(setq durationList (car (cdr (cdr paramList))))

	;list of tuples that will be return
	(setq tupleList nil)
	
	;temporary sublists
	(setq tempPitchList pitchList)
	(setq tempOnsetList onsetList)
	(setq tempDurationList durationList)
	
	(loop while (not (null (car tempPitchList)) ) do
		
		(setq tupleList (cons (list (car tempPitchList) (car tempOnsetList) (car tempDurationList)) tupleList))
		
		(setq tempPitchList (cdr tempPitchList))
		(setq tempOnsetList (cdr tempOnsetList))
		(setq tempDurationList (cdr tempDurationList))
	)
	
	(setq toReturn tupleList)
	
	
)


;creates a list of tuples of arity 3 from a list of tuples of arity 5 (ie only get the 3 first elements of each list)
;tuples are here Common Lisp lists
(defun subTupleList3_5 (tupleList_5)
	
	;list to be returned
	(setq tupleList_3 nil)
	
	(loop while (not (null (car tupleList_5)) ) do
		
		(setq tempTuple (car tempTupleList))
		
		(setq tupleList_3 (cons (list (car tempTuple) (car (cdr tempTuple)) (car (cdr (cdr tempTuple)))) tupleList_3))
		
		(setq tempTupleList (cdr tempTupleList))
	)
	
	(setq tupleList_3 tupleList_3)
)



;create a list of tuple uuids. the set of tuples will be a ground relation complete ground relation bounded for each component (ternary relation)
; (defun createTupleUUIDListForBoundedFullGroundRelation (gm minMaxList)
; 	
; 	;get the different bounds
; 	(setq pitch_min (car minMaxList))
; 	(setq minMaxList (cdr minMaxList))
; 	
; 	(setq pitch_max (car minMaxList))
; 	(setq minMaxList (cdr minMaxList))
; 	
; 	(setq onset_min (car minMaxList))
; 	(setq minMaxList (cdr minMaxList))
; 	
; 	(setq onset_max (car minMaxList))
; 	(setq minMaxList (cdr minMaxList))
; 	
; 	(setq duration_min (car minMaxList))
; 	(setq minMaxList (cdr minMaxList))
; 	
; 	(setq duration_max (car minMaxList))
; 	
; 	;list of tuple uuids
; 	(setq tupleUUIDList nil)
; 	
; 	(loop for tempPitch from pitch_min to pitch_max do
; 		
; 		(loop for tempOnset from onset_min to onset_max do
; 			
; 			(loop for tempDuration from duration_min to duration_max do
; 				
; 				;the new tuple
; 				(setq tempTuple (newTuple gm (append (list tempPitch) (list tempOnset) (list tempDuration))))
; 				
; 				(setq tupleUUIDList (append tupleUUIDList (list tempTuple)))
; 			)
; 		)
; 	)
; 	(setq toReturn tupleUUIDList)
; )



;returns the minimum and maximum values of parameters (ternary relation)
(defun getMinMaxParamValues (tupleList)

	(setq minPossibleVal 0) ; min val number in relations
	(setq maxPossibleVal (- (expt 2 32) 1)) ; max val number in relations

	;initial list of parameters (minPitch maxPitch minOnset maxOnset minDuration maxDuration)
	;it will be updated afterwards
	(setq minMaxParamList (list maxPossibleVal minPossibleVal maxPossibleVal minPossibleVal maxPossibleVal minPossibleVal))
		
	;loop on tuple
	(loop while (first tupleList) do

		;current tuple
		(setq tempTuple (car TupleList))
		
		;will contain the new list of parameters after iteration
		(setq newMinMaxParamList nil)

		;loop on all values of the current tuple
		(loop while (not (null (car tempTuple)) ) do
			
			;first min parameter
			
			;if the value is smaller in this tuple that the minimum value until now, we use that one in the new list of parameters
			;otherwise we use the other
			(if (< (car tempTuple) (car minMaxParamList))
				(setq newMinMaxParamList (cons (car tempTuple) newMinMaxParamList))
				(setq newMinMaxParamList (cons (car minMaxParamList) newMinMaxParamList))
			)
			
			;max parameter
			(setq minMaxParamList (cdr minMaxParamList))
			
			;if the value is bigger in this tuple that the maximum value until now, we use that one in the new list of parameters
			;otherwise we use the other
			(if (> (car tempTuple) (car minMaxParamList))
		    	(setq newMinMaxParamList (cons (car tempTuple) newMinMaxParamList))
				(setq newMinMaxParamList (cons (car minMaxParamList) newMinMaxParamList))
			)
			
			;next parameter
			(setq minMaxParamList (cdr minMaxParamList))
			(setq tempTuple (cdr tempTuple))
			
		)
		
		;update the list of parameters
		(setq minMaxParamList (reverse newMinMaxParamList))
		
		;next tuple
		(setq tupleList (cdr tupleList))
	)
	
	;return the value
	(setq minMaxParamList minMaxParamList)
	
)


;creates a list of minmaxparam that includes two lists of minmaxparam 
(defun getMinMaxParamValuesFrom2 (minMax1 minMax2)
	
	(setq tempMinMax1 minMax1)
	(setq tempMinMax2 minMax2)
	
	(setq newMinMax nil)
	
	;loop on tuples
	(loop while (not (null (car tempMinMax1)) ) do
		
		;first min parameter
		
		;min comparison
		(if (< (car tempMinMax1) (car tempMinMax2))
			(setq newMinMax (cons (car tempMinMax1) newMinMax))
			(setq newMinMax (cons (car tempMinMax2) newMinMax))
		)
		
		;max parameter
		(setq tempMinMax1 (cdr tempMinMax1))
		(setq tempMinMax2 (cdr tempMinMax2))
		
		;max comparison
		(if (> (car tempMinMax1) (car tempMinMax2))
			(setq newMinMax (cons (car tempMinMax1) newMinMax))
			(setq newMinMax (cons (car tempMinMax2) newMinMax))
		)
		
		;next parameter
		(setq tempMinMax1 (cdr tempMinMax1))
		(setq tempMinMax2 (cdr tempMinMax2))

		
	)
	
	(setq newMinMax (reverse newMinMax))
	
)


;from the list l, create a list of list, in which every element is the list l concatenated with one of the element between i and j
; l is a list of integers
; i and j are integers and i <= j
(defun appendListWithIntegers (l i j)
	
	(setq listOfLists nil)
	
	;other elements
	(loop for x from i to j do
	        (push (append l (list x)) listOfLists)
	)
	
	(setq listOfLists listOfLists)
	
)


;create a list of tuples (as lisp lists) from component bounds
;boundsList is a list of pairs (min max), where min is the min value of the component and max 
;is the max value of that component
;the tuples are of arity (length boundsList) / 2	

(defun createLispTupleFromBounds (boundsList)
	
	;temporary list of tuples, initialized with unary tuples for the first component bounds
	(setq tempTupleList (appendListWithIntegers nil (first (first boundsList)) (second (first boundsList))))
	
	;the first component is already done, so we skip it
	(setq boundsList (rest boundsList))
	
	(loop while (first boundsList) do
		
		;will be the list updated with the new component
		(setq tempUpdatedTupleList nil)
		
		(loop while (first tempTupleList) do
		
			;we create a list of tuples from current tuple and current bounds
			(setq newListTuplesWithCurrentBoundsAdded (appendListWithIntegers (first tempTupleList) (first (first boundsList)) (second (first boundsList))))
		
			;we add that tuple list to the new updated list
			(setq tempUpdatedTupleList (append newListTuplesWithCurrentBoundsAdded tempUpdatedTupleList))
		
			;next tuple of the temporary list
			(setq tempTupleList (rest tempTupleList))
		)
		
		;the tuple list is now the updated list
		(setq tempTupleList tempUpdatedTupleList)
		
		;next component bounds
		(setq boundsList (rest boundsList))
	)

	(setq finalTupleList tempTupleList)
)

;create Gecode tuple uuid list from lisp tuple uuid list
;gm is a well initiated gecode manager
(defun createTupleUUIDListFromLispTupleList (gm lispTupleList)

	(let (
			(i 0)
			(curT (get-internal-real-time))
		 )

	(setq finalTupleUUIDList nil)
	
	(print "we will create a list of" )
	(print (length lispTupleList))
	(print "tuples" )
	
	(loop while (first lispTupleList) do
		
		(if (= (mod i 100) 0)
			(progn
				(print i)
				(print (- (get-internal-real-time) curT))
				(print "seconds")
				(setq curT (get-internal-real-time))
			)
			)
		
		;a new tuple
		(setq tempTuple (newTuple gm (first lispTupleList)))
		
		;add the new uuid tuple to the list
		(setq finalTupleUUIDList (append finalTupleUUIDList (list tempTuple)))
		
		(setq lispTupleList (rest lispTupleList))
		
		(setq i (+ i 1))
	)
	
	(setq finalTupleUUIDList finalTupleUUIDList)
	
	)
)


;create a ground relation containing all the tuples identified in tupleUUIDList
;pre : gm is a well initialized Gecode Manager 
;		the tuples all have the same arity
(defun createGroundRelFromTupleUUIDList (gm tupleUUIDList)

	;get the arity of the first tuple (equal to arity of the ground relation to be constructed)
	(setq arity (getTupleArity gm (first tupleUUIDList)))

	;empty ground relation
	(setq gr (newGRelation gm arity))
		
	;while there are tuple uuids in the list, we continue adding tuple	
	(loop while (first tupleUUIDList) do
		
		;add the tuple
		(GRelation-AddTuple gm gr (first tupleUUIDList))
		
		(setq tupleUUIDList (cdr tupleUUIDList))
	)
	
	(setq toReturn gr)
	
	
)


;creates a complete ground relation bounded for each component
;pre : gm is a well initialized Gecode Manager 
;return a list in which the first element is the ground relation uuid and the second is the list of tuple uuid
;minMaxList is a list of couples (min and max value of a given component)
(defun createBoundedFullGroundRelation (gm minMaxList)
	
	;lisp tuple list
	
	(print "will create lisp tuples")
	(setq lispTupleList (createLispTupleFromBounds minMaxList))
	(print "lisp tuples : done")
	
	;tuple UUID list
	(print "will create uuid tuples")
	(setq tupleUUIDList (createTupleUUIDListFromLispTupleList gm lispTupleList))
	(print "uuid tuples : done")
	
	;ground relation
	(print "will create gr")
	(setq gr (createGroundRelFromTupleUUIDList gm tupleUUIDList))
	(print "gr : done")
	
	(setq toReturn (concatenate 'list (list gr) (list tupleUUIDList)))
)