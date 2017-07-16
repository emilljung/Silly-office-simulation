require "Person"
require "Room"
require "CoffeeConsumer"
require "Rager"
require "Leader"

GameEngine.PrintNameVr()
GameEngine.Print("Press and hold 'Q' to exit the program!\n")

rooms = { Room:new("Office1"),
          Room:new("Office2"),
          Room:new("Office3"),
          Room:new("Corridor"), 
          Room:new("CoffeeRoom") }

employee = {  newLeader(Person:new("Engelbrekt", rooms[1])),
              newRager(Person:new("Petter", rooms[2]), 0),
              newCoffeeConsumer(Person:new("Nicklas", rooms[3]), 2) }
			  
print()

for i=1, 3, 1 do
    employee[i]:getParent():SetRoomTable(rooms)
end

employee[1]:setEmployeeTable(employee)  -- Så att Leader kan hålla koll på Rager & CoffeeConsumer

math.randomseed(os.time()) -- För att Rager ska kunna använda math.random(x,y)


function GameLoop()	
	GameEngine.SetLoopActive(GameEngine.GetInput())

    employee[1]:update()
    employee[2]:update()
    employee[3]:update()
    print()
	
	return 1
end

--(<loop-tid i sec>, <funktion som ska upprepas>)
GameEngine.SetMainLoop(0.5, GameLoop)
