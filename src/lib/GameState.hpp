#ifndef __GAMESTATE_
#define __GAMESTATE_

#include <map>
#include <string>

/*
 * Kelas abstrak yang digunakan untuk mengeksekusi logic sebuah state di dalam
 * game. Kelas ini beserta turunannya dimaksudkan agar digunakan di dalam game
 * loop.
 */
class GameState
{
  public:
    GameState(bool end);

    /**
     * @brief Method yang mengindikasikan state akhir dari game.
     * @return true jika state ini adalah penanda akhir dari game.
     */
    bool isEnd();

    /**
     * @brief Method abstrak untuk mengeksekusi logic dalam sebuah state.
     * @return state selanjutnya yang harus dieksekusi
     */
    virtual GameState* updateState() = 0;
    virtual ~GameState() = default;

    /**
     * @brief Meregister state game yang akan dipakai selama game berjalan.
     *
     * @param name nama state
     * @param state state yang akan diregister
     */
    static void registerState(std::string name, GameState* state);

    /**
     * @brief Mengambil objek GameState dengan nama tertentu.
     *
     * @param name nama state saat diregister
     * @return game state dengan nama yang sesuai saat diregister
     * @throw std::out_of_range jika tidak ada state dengan nama yang sesuai
     */
    static GameState* getState(std::string name);

    /*
     * @brief Membersihkan map states (termasuk delete pointer)
     * Karena value dari states adalah sebuah pointer, maka semuanya harus
     * didelete secara manual. Penggunaan method ini diserahkan pada pengguna.
     */
    static void clearStates();

  protected:
    /**
     * @brief Flag penanda state terakhir dari game.
     */
    bool end;

  private:
    /**
     * @brief Map untuk menyimpan state yang telah diregister
     */
    static std::map<std::string, GameState*> states;
};

#endif // !__GAMESTATE_
