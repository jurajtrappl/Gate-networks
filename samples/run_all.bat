@echo off

echo =================
echo SIMPLE GATE TESTS
echo =================

echo --------
echo AND GATE
echo --------

echo Expected Output:
type AND\expected.txt

echo Output:
..\build-x64\Release\GateNetworks.Application.exe AND\AND_gate.in < AND\cmd.in > AND\output.out
type AND\output.out

echo Result:
fc AND\expected.txt AND\output.out >NUL && echo SUCCESS || echo FAILED
del AND\output.out

echo -------
echo OR GATE
echo -------

echo Expected Output:
type OR\expected.txt

echo Output:
..\build-x64\Release\GateNetworks.Application.exe OR\OR_gate.in < OR\cmd.in > OR\output.out
type OR\output.out

echo Result:
fc OR\expected.txt OR\output.out >NUL && echo SUCCESS || echo FAILED
del OR\output.out

echo ==================
echo COMPLEX GATE TESTS
echo ==================

echo ----------------
echo AND and OR GATES
echo ----------------

echo Expected Output:
type AND_and_OR\expected.txt

echo Output:
..\build-x64\Release\GateNetworks.Application.exe AND_and_OR\AND_and_OR_gates.in < AND_and_OR\cmd.in > AND_and_OR\output.out
type AND_and_OR\output.out

echo Result:
fc AND_and_OR\expected.txt AND_and_OR\output.out >NUL && echo SUCCESS || echo FAILED
del AND_and_OR\output.out

echo ------------------
echo NETWORK WITH CYCLE
echo ------------------

echo Expected Output:
type CYCLE\expected.txt

echo Output:
..\build-x64\Release\GateNetworks.Application.exe CYCLE\cycle.in < CYCLE\cmd.in > CYCLE\output.out
type CYCLE\output.out

echo Result:
fc CYCLE\expected.txt CYCLE\output.out >NUL && echo SUCCESS || echo FAILED
del CYCLE\output.out