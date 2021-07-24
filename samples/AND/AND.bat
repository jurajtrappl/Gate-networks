@echo off

echo --------
echo AND GATE
echo --------

echo Expected Output:
type expected.txt

echo Output:
..\..\build-x64\Release\GateNetworks.Application.exe AND_gate.in < cmd.in > output.out
type output.out

echo Result:
fc expected.txt output.out >NUL && echo SUCCESS || echo FAILED
del output.out