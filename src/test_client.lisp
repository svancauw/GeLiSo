(require "comm")

;start-up-server

;process-kill

;open-tcp-stream

;socket-stream

;(with-open-stream ...)

;	read-sequence
;write-sequence

;make-array

;wait-for-input-streams

(defun connection_test ()
	;OK !
	;(comm:open-tcp-stream "127.0.0.1" 2222)


	(with-open-stream 
		(tcp_str 
	    	(comm:open-tcp-stream "localhost" 2222 :element-type 'base-char)
		)
		;(let 
		;	((res (make-array 128 :element-type 'base-char)))
		;	(values (read-sequence res tcp_str) res)
		;)
		(write-sequence "Test !!! " tcp_str)
		
	)
		
	
	
)

