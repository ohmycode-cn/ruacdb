#ifndef TERMLITE_RUAC_WINDOW_HPP
#define TERMLITE_RUAC_WINDOW_HPP

namespace ruac::terminal_lite {

    class Window final {
      public:
        Window() = default;
        ~Window() = default;

      public:
        static void run(int argc, char **argv);
    };

} // namespace ruac::terminal_lite

#endif // TERMLITE_RUAC_WINDOW_HPP
