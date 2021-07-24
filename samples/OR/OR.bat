@echo off

echo -------
echo OR GATE
echo -------

echo Expected Output:
type expected.txt

echo Output:
..\..\build-x64\Release\GateNetworks.Application.exe OR_gate.in < cmd.in > output.out
type output.out

echo Result:
fc expected.txt output.out >NUL && echo SUCCESS || echo FAILED
del output.out