@echo off

echo ------------------
echo NETWORK WITH CYCLE
echo ------------------

echo Expected Output:
type expected.txt

echo Output:
..\..\build-x64\Release\GateNetworks.Application.exe cycle.in < cmd.in > output.out
type output.out

echo Result:
fc expected.txt output.out >NUL && echo SUCCESS || echo FAILED
del output.out