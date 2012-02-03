

letterAtlas = {}
for y = 1, 8 do
   for x = 1, 8 do
      table.insert(letterAtlas,
                   {x = (x-1) * 64,
                    y = (y-1) * 64,
                    width = 64,
                    height = 64})
   end
end


function init(scene)

   local resman = scene_getResourceManager(scene)
   
   resman_loadTexture(resman, "letters.png")

   local numTiles = #letterAtlas
   local atlas = resman_makeTextureAtlas(resman, "letters", "letters.png", numTiles)
   
   for i, v in ipairs(letterAtlas) do
      texatlas_setTile(atlas, i-1, v.x, v.y, v.width, v.height)
   end
   
end

