function newCoffeeConsumer(baseClass, nrOfCoffee)
    print(baseClass:GetName() .. ": 'Yum! " .. nrOfCoffee .. " filled coffee cups are here :)'")

    local cc = {  coffee = nrOfCoffee,
                  base = baseClass }

    function cc:getParent()
        return self.base
    end
    
    function cc:drink()
        self.coffee = self.coffee - 1
        print(cc:getParent():GetName() .. " is drinking... " .. self.coffee .. " are left")
    end
    
    function cc:fill()
        self.coffee = self.coffee + 1
        print(cc:getParent():GetName() .. " is filling 1 coffee cup... ")
        if self.coffee == 1 then
            print(cc:getParent():GetName() .. ": '".. self.coffee .. " of 3 is ready to be consumed!'")
        else
            print(cc:getParent():GetName() .. ": '".. self.coffee .. " of 3 are ready to be consumed!'")
        end
    end
    
    function cc:update()
        if self.base:GetRoom():GetRoomName() == "Office3" then
            if cc:inOffice() then
                cc:getParent():MoveTo(self.base:GetRoomTable()[4]) -- Till Corridor
            end
        elseif self.base:GetRoom():GetRoomName() == "Corridor" then
            if cc:inCorridor() then
                cc:getParent():MoveTo(self.base:GetRoomTable()[3]) -- Till Office3
            else
                cc:getParent():MoveTo(self.base:GetRoomTable()[5]) -- Till CoffeeRoom
            end
        else
            if cc:inCoffeeRoom() then
                cc:getParent():MoveTo(self.base:GetRoomTable()[4]) -- Till Corridor
            end          
        end
    end
    
    function cc:inOffice()
        move = false -- Stanna kvar i Office3 och drick kaffe
        
        -- if self.coffee != 0
        if self.coffee ~= 0 then
            cc:drink()
        else
            move = true
            print(cc:getParent():GetName() .. ": 'Darn it, the cups are empty! I go and get some more...'")
        end
        
        return move
    end
    
    function cc:inCorridor()
        move = false -- Gå till CoffeeRoom
        
        if self.coffee ~= 0 then
            move = true --Gå till Office3
        end
        
        return move
    end
    
    function cc:inCoffeeRoom()
        move = false -- Stanna kvar i CoffeeRoom och fyll koppar med kaffe
        if self.coffee < 3 then
            cc:fill()
        else
            print(cc:getParent():GetName() .. ": 'The Coffee cups are filled! Time to go back'")
            move = true -- Gå till Corridor
        end
        return move
    end

    return cc
end