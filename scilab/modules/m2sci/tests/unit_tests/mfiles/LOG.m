% Test file for function log()
% Matlab version: 7.9.0.529 (R2009b)

% TEST 1
res1 = log([]);
% TEST 2
res2 = log(m2sciUnknownType([]));
% TEST 3
res3 = log(m2sciUnknownDims([]));
% TEST 4
res4 = log([1]);
% TEST 5
res5 = log([1,2,3]);
% TEST 6
res6 = log([1;2;3]);
% TEST 7
res7 = log([1,2,3;4,5,6]);
% TEST 8
res8 = log(m2sciUnknownType([1]));
% TEST 9
res9 = log(m2sciUnknownType([1,2,3]));
% TEST 10
res10 = log(m2sciUnknownType([1;2;3]));
% TEST 11
res11 = log(m2sciUnknownType([1,2,3;4,5,6]));
% TEST 12
res12 = log(m2sciUnknownDims([1]));
% TEST 13
res13 = log(m2sciUnknownDims([1,2,3]));
% TEST 14
res14 = log(m2sciUnknownDims([1;2;3]));
% TEST 15
res15 = log(m2sciUnknownDims([1,2,3;4,5,6]));
% TEST 16
res16 = log([i]);
% TEST 17
res17 = log([i,2i,3i]);
% TEST 18
res18 = log([i;2i;3i]);
% TEST 19
res19 = log([i,2i,3i;4i,5i,6i]);
% TEST 20
res20 = log(m2sciUnknownType([i]));
% TEST 21
res21 = log(m2sciUnknownType([i,2i,3i]));
% TEST 22
res22 = log(m2sciUnknownType([i;2i;3i]));
% TEST 23
res23 = log(m2sciUnknownType([i,2i,3i;4i,5i,6i]));
% TEST 24
res24 = log(m2sciUnknownDims([i]));
% TEST 25
res25 = log(m2sciUnknownDims([i,2i,3i]));
% TEST 26
res26 = log(m2sciUnknownDims([i;2i;3i]));
% TEST 27
res27 = log(m2sciUnknownDims([i,2i,3i;4i,5i,6i]));