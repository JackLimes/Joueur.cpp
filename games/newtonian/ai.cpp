/* GIT TESTING */
// AI
// This is where you build your AI

#include "ai.hpp"

// <<-- Creer-Merge: includes -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// You can add #includes here for your AI.
// <<-- /Creer-Merge: includes -->>
#include <iostream>

namespace cpp_client
{

namespace newtonian
{

/// <summary>
/// This returns your AI's name to the game server.
/// Replace the string name.
/// </summary>
/// <returns>The name of your AI.</returns>
std::string AI::get_name() const
{
    // <<-- Creer-Merge: get-name -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // REPLACE WITH YOUR TEAM NAME!
    return "Team Orange";
    // <<-- /Creer-Merge: get-name -->>
}

/// <summary>
/// This is automatically called when the game first starts, once the game objects are created
/// </summary>
void AI::start()
{
    // <<-- Creer-Merge: start -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // This is a good place to initialize any variables
    // <<-- /Creer-Merge: start -->>
}

/// <summary>
/// This is automatically called the game (or anything in it) updates
/// </summary>
void AI::game_updated()
{
    // <<-- Creer-Merge: game-updated -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // If a function you call triggers an update this will be called before it returns.
    // <<-- /Creer-Merge: game-updated -->>
}

/// <summary>
/// This is automatically called when the game ends.
/// </summary>
/// <param name="won">true if you won, false otherwise</param>
/// <param name="reason">An explanation for why you either won or lost</param>
void AI::ended(bool won, const std::string& reason)
{
    //<<-- Creer-Merge: ended -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // You can do any cleanup of your AI here.  The program ends when this function returns.
    //<<-- /Creer-Merge: ended -->>
}

/// <summary>
/// This is called every time it is this AI.player's turn.
/// </summary>
/// <returns>Represents if you want to end your turn. True means end your turn, False means to keep your turn going and re-call this function.</returns>
bool AI::run_turn()
{
  std::cout << "Turn: " << game->current_turn << std::endl;
  std::cout << "0" << std::endl;
  for (unsigned int unitNum = 0; unitNum < player->units.size(); unitNum++)
  {
    std::cout << "1" << std::endl;
    
    if(player->units[unitNum]->job->title == "physicist")
    {
      std::cout << "2" << std::endl;
      //std::vector<Tile> path = find_path(player->units[unitNum]->tile, game->get_tile_at(3,7));
      //std::cout << "Size:" << path.size() << std::endl;
      //std::cout << "Nav: " << game->get_tile_at(3,7)->is_pathable() << std::endl;
      //player->units[unitNum]->move(path[0]);
      physThinkBlue(player->units[unitNum]);
    }
    
    if(player->units[unitNum]->job->title == "intern")
    {
      snatch_blue_ore(player->units[unitNum]);
    }
  }
  // <<-- Creer-Merge: runTurn -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
  // Put your game logic here for run_turn here
  // <<-- /Creer-Merge: runTurn -->>
  std::cout << std::endl;
  
  return true;
}

/// A very basic path finding algorithm (Breadth First Search) that when given a starting Tile, will return a valid path to the goal Tile.
/// <param name="start">the starting Tile</param>
/// <param name="goal">the goal Tile</param>
/// <return>A List of Tiles representing the path, the the first element being a valid adjacent Tile to the start, and the last element being the goal. Or an empty list if no path found.</return>
std::vector<Tile> AI::find_path(const Tile& start, const Tile& goal)
{
    // no need to make a path to here...
    if(start == goal)
    {
        return {};
    }

    // the tiles that will have their neighbors searched for 'goal'
    std::queue<Tile> fringe;

    // How we got to each tile that went into the fringe.
    std::unordered_map<Tile,Tile> came_from;

    // Enqueue start as the first tile to have its neighbors searched.
    fringe.push(start);

    // keep exploring neighbors of neighbors... until there are no more.
    while(fringe.size() > 0)
    {
        // the tile we are currently exploring.
        Tile inspect = fringe.front();
        fringe.pop();

        // Note, we are using the `auto` keyword here
        //   The compiler can discern that this is a `std::vector<Tile>` based on the return type of `getNeighbors()`
        auto neighbors = inspect->get_neighbors();

        // cycle through the tile's neighbors.
        for(unsigned i = 0; i < neighbors.size(); i++)
        {
            Tile neighbor = neighbors[i];

            // If we found the goal we've found the path!
            if(neighbor == goal)
            {
                // Follow the path backward starting at the goal and return it.
                std::deque<Tile> path;
                path.push_front(goal);

                // Starting at the tile we are currently at, insert them retracing our steps till we get to the starting tile
                for(Tile step = inspect; step != start; step = came_from[step])
                {
                    path.push_front(step);
                }

                // we want to return a vector as that's what we use for all containers in C++
                // (and they don't have push_front like we need)
                // So construct the vector-ized path here
                std::vector<Tile> vector_path;
                for(auto& tile : path)
                {
                    vector_path.push_back(tile);
                }
                return vector_path;
            }

            // if the tile exists, has not been explored or added to the fringe yet, and it is pathable
            if(neighbor && came_from.count(neighbor) == 0 && neighbor->is_pathable())
            {
                // add it to the tiles to be explored and add where it came from.
                fringe.push(neighbor);
                came_from[neighbor] = inspect;
            }

        } // for each neighbor

    } // while fringe not empty

    // if you're here, that means that there was not a path to get to where you want to go.
    //   in that case, we'll just return an empty path.
    return {};
}

//<<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// You can add additional methods here for your AI to call
//<<-- /Creer-Merge: methods -->>
void AI::physThinkBlue(const Unit& physicist)
{
/*
 std::cout << "3" << std::endl;
  //get to the nearest blue oar.
  std::vector<Tile> shortestPath;
  bool ignore_start = true; // since start with empty vector, don't want that to be the shortest path
  for(unsigned i = 0; i < game->tiles.size(); i++)
  {
    if (game->tiles[i]->blueium_ore > 0)
    {
      std::cout << "I probably got here!" << std::endl;
      std::vector<Tile> adjacent = game->tiles[i]->get_neighbors();
      for(unsigned j = 0; j < adjacent.size(); j++)
      {
        if(adjacent[j]->is_pathable())
        {
          shortestPath = find_path(physicist->tile, adjacent[j]);
          break;
        }
      }
    }
  }
  std::cout << "4" << std::endl;
  //std::cout << shortestPath[0]->x << ":" << shortestPath[0]->y << std::endl;
  if(shortestPath.size() > 0)
  { 
    std::cout << "I moved!" << std::endl;
    physicist->move(shortestPath[0]);
  }
*/

  std::vector<Tile> path = find_path(physicist->tile, physicist->tile->tile_south->tile_east);
  std::cout << "path_size: " << path.size() << std::endl;
  if(path.size() > 0) 
  {
    physicist->move(path[0]);
  }
}

void AI::snatch_blue_ore(const Unit& unit)
{
  std::cout << "phy" << std::endl;
  std::vector<Tile> path;
  for(unsigned i = 0; i < game->tiles.size(); i++)
  {
    if(game->tiles[i]->blueium_ore > 0)
    {
      std::cout << "found blue at: " << game->tiles[i]->x << ", " << game->tiles[i]->y << std::endl;
      path = find_path(unit->tile, game->get_tile_at(25,5));
      std::cout << "path_size: " << path.size() << std::endl;
      break;
    }
  }
  if(path.size() > 0)
  {
    std::cout << "I'm moving to blue!" << std::endl;
    unit->move(path[0]);
  }
    
  return;
}

} // newtonian

} // cpp_client
