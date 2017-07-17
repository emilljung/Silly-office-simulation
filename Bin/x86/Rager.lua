function newRager(baseClass, rage)
    -- Print this when a Rager is created
    print(baseClass:GetName() .. ": 'Phu, I'm actually quite calm today!'")
    
    local rager = { base = baseClass,
                    rageMeter = rage }

    function rager:getParent()
        return self.base
    end

    function rager:update()
        if self.base:GetRoom():GetRoomName() == "Office2" then
            if rager:inOffice() then
                rager:getParent():MoveTo(self.base:GetRoomTable()[4]) -- To Corridor
            end
        else            
            if rager:inCorridor() then
                rager:getParent():MoveTo(self.base:GetRoomTable()[2]) -- To Office2
            end         
        end
    end
    
    function rager:inOffice()
        move = false    -- Stay in Office2
        val = math.random(-1,1)
        
        if val == 1 then
            -- Rager is getting more angry
            self.rageMeter = self.rageMeter + 1
            if self.rageMeter == 1 then
                print(rager:getParent():GetName() .. ": 'This is more difficult than I expected...' ")
            elseif self.rageMeter == 2 then
                print(rager:getParent():GetName() .. ": 'Grrr...' ")
            else
                print(rager:getParent():GetName() .. ": 'Fuck this shit!' ")
                move = true   -- Go to Corridor
            end
        elseif val == -1 then
            -- Rager is getting calmer
            if self.rageMeter > 0 then
                self.rageMeter = self.rageMeter - 1
                if self.rageMeter == 2 then
                    print(rager:getParent():GetName() .. ": 'Ok... try to calm down...' ")
                elseif self.rageMeter == 1 then
                    print(rager:getParent():GetName() .. ": 'Hmm... ' ")
                else
                    print(rager:getParent():GetName() .. ": 'It works! Good thing I'm so calm :)' ")
            end
            else
                -- Tries to get more calm than 0.
                print(rager:getParent():GetName() .. ": 'I'm so calm I could fall asleep!' ")
            end
        else
            -- Unchanged anger, val == 0
            print(rager:getParent():GetName() .. ": 'This is so annoying...' ")
        end
        
        return move
    end
    
    function rager:inCorridor()
        move = false  -- Stay in Corridor
        
        -- Calm down step wise
        if self.rageMeter > 0 then
            self.rageMeter = self.rageMeter - 1
            print(rager:getParent():GetName() .. ": 'Calm down " .. rager:getParent():GetName() .. "... Calm down...' ")
        else
            print(rager:getParent():GetName() .. ": 'Time to go back to my office!' ")
            move = true -- Go to Office2        
        end
        
        return move
    end

    return rager
end 
