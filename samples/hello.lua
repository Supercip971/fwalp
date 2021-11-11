
render = require "fwalp_renderer"
color = require "fwalp_color"

final_res_color = color.blue
function update(time)
    print ("updated: " ..  time)

    if time > 50 and time < 100 then
        final_res_color = color.red
    elseif time > 100 then 
        final_res_color = color.green 
    end
end

function draw()
    render:set_color(final_res_color)

    render:draw_rec(100, 100, 100, 100)
end

