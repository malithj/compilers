define void @bubble_sort(i32* %a) {
	%i = alloca i32 ;allocate i
	%j = alloca i32 ;allocate j
	%tmp = alloca i32 ;allocate tmp
	store i32 0, i32* %i
	store i32 1, i32* %j
	store i32 0, i32* %tmp
	br label %cond_i

cond_i:
	%t1 = load i32, i32* %i
	%t2 = icmp slt i32 %t1, 10
	store i32 1, i32* %j
	br i1 %t2, label %cond_j, label %end

cond_j:
	%t3 = load i32, i32* %j
        %t16 = sub i32 %t3, 1
	%t8 = getelementptr i32, i32* %a, i32 %t16
	%t9 = getelementptr i32, i32* %a, i32 %t3
	%t12 = load i32, i32* %t8
	%t13 = load i32, i32* %t9
	%t10 = icmp sgt i32 %t12, %t13
	br i1 %t10, label %cond_swap, label %cond_j_end

cond_swap:
	store i32 %t12, i32* %tmp 
	store i32 %t13, i32* %t8
	%t14 = load i32, i32* %tmp
	store i32 %t14, i32* %t9
	br label %cond_j_end


cond_j_end:
	%t4 = icmp slt i32 %t3, 9
	%t6 = add i32 %t3, 1 ;update i and j
	store i32 %t6, i32* %j
	br i1 %t4, label %cond_j, label %cond_i_end

cond_i_end:
	%t7 = add i32 %t1, 1
	store i32 %t7, i32* %i
	br label %cond_i

end:
	ret void
}


define void @recursive_bubble_sort(i32* %a) {
	%i = alloca i32 ;allocate i
	%n = alloca i32 ;allocate n
	%idx = alloca i32 ;allocate idx
	store i32 0, i32* %i
	store i32 10, i32* %n
	store i32 10, i32* %idx
	br label %cond_i

cond_i:
	%t1 = load i32, i32* %i
	%t2 = icmp slt i32 %t1, 10
	br i1 %t2, label %body, label %end

body:
	%t3 = load i32, i32* %n
        store i32 0, i32* %idx
	call i32 @r_bubble_sort(i32* %a, i32 %t3, i32* %idx)
	br label %cond_i_end	

cond_i_end:
	%t7 = add i32 %t1, 1
	store i32 %t7, i32* %i
	br label %cond_i

end:
	ret void
}


define i32 @r_bubble_sort(i32* %a, i32 %n, i32* %idx) {
	%tmp = alloca i32 ;allocate tmp
	%t1 = sub i32 %n, 1
	%t2 = load i32, i32* %idx
	%t3 = icmp eq i32 %t2, %t1
	br i1 %t3, label %end, label %body

body:
	%t5 = add i32 %t2, 1
	store i32 %t5, i32* %idx
	%t6 = call i32 @r_bubble_sort(i32* %a, i32 %n, i32* %idx)
	%t7 = load i32, i32* %idx
	%t8 = sub i32 %t7, 1
	store i32 %t8, i32* %idx
	%t9 = getelementptr i32, i32* %a, i32 %t8
	%t10 = load i32, i32* %t9
	%t11 = icmp slt i32 %t6, %t10
	br i1 %t11, label %swap, label %no_swap


swap:
	store i32 %t10, i32* %tmp 
	store i32 %t6, i32* %t9
	%t12 = load i32, i32* %tmp
	%t13 = getelementptr i32, i32* %a, i32 %t5
	store i32 %t12, i32* %t13
	ret i32 %t6

no_swap:
	ret i32 %t10

end:
	%t4 = getelementptr i32, i32* %a, i32 %t2
	%t14 = load i32, i32* %t4
	ret i32 %t14
}
