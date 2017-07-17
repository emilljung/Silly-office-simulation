Person = {}

-- Parent class to Leader, Rager & CoffeeConsumer. All the sub classes have access to these functions. 

function Person:new(p_name, p_room)
    print(p_name .. " is starting in " .. p_room:GetRoomName())

    local person = {  name = p_name,
                      room = p_room,
                      r_table = nil }
    
    function person:GetName()
        return self.name
    end
    
    function person:GetRoom()
        return self.room
    end
    
    function person:GetRoomTable()
        return self.r_table
    end
    
    function person:SetRoomTable(table)
       self.r_table = table
    end
    
    function person:MoveTo(room)
        self.room = room
        print(self.name .. " went to " .. self.room:GetRoomName())
    end
    
    return person
end
