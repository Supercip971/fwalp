
render = require "fwalp_renderer"
color = require "fwalp_color"
final_res_color = color.blue

rec_x = 1.0
rec_y = 1.0
rec_width = 16
rec_height = 16
dir_x = 1.0
dir_y = 1.0
t = 0
function update(time, dt)
    print ("updated: " ..  time .. " fps: " ..1/dt .. " with: " .. dt)

    if time > 50 and time < 100 then
        final_res_color = color.red
    elseif time > 100 then
        final_res_color = color.green
    end


    if rec_x + rec_width + 5 >= render:screen_width() then
        dir_x = -1.0
    elseif rec_x < 5 then
        dir_x = 1.0
    end

    if rec_y + rec_height + 5 >= render:screen_height() then
        dir_y = -1.0
    elseif rec_y < 5 then
        dir_y =1.0 
    end

    rec_x = rec_x + (dir_x * dt * 15)
    rec_y = rec_y + (dir_y * dt * 15)

    t = time
    print ("recx: " .. rec_x .. " recy: " .. rec_y)

end

function draw()
    render:set_color(color.black)
    render:fill()
    render:set_color(final_res_color)
    base = render:screen_height() / 2
    for i = 1, render:screen_width() do
        res = base + math.sin(i / 10 + t) * 50
        render:draw_rec(tonumber(i), tonumber(res), 1,1)
    end



end

