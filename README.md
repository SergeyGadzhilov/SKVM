# SKVM

### What is it?

SKVM is software that mimics the functionality of a KVM switch, which
historically would allow you to use a single keyboard and mouse to control
multiple computers by physically turning a dial on the box to switch the machine
you're controlling at any given moment. SKVM does this in software, allowing
you to tell it which machine to control by moving your mouse to the edge of the
screen, or by using a keypress to switch focus to a different system.

At the moment, SKVM is not compatible with Synergy.

SKVM needs to be installed on all machines that will share keyboard and
mouse.

### Usage

1. Install and run on each machine that will be sharing.
2. On the machine with the keyboard and mouse, make it the server.
3. Click the "Configure server" button and drag a new screen onto the grid for
   each client machine.
4. Ensure the "screen name" matches exactly (case-sensitive) for each configured
   screen -- the clients' SKVM windows will tell you their screen names
   (just above the server IP).
5. On the client(s), put in the server machine's IP address (or use Bonjour/auto
   configuration when prompted) and "start"t hem.

You should see `SKVM is running` on both server and clients.

You should now be able to move the mouse between all the screens as if they were
the same machine.

Note that if the keyboard's Scroll Lock is active then this will prevent the
mouse from switching screens.

### Contact & support

Please be aware that the _only_ way to draw attention to a bug is to create
a new issue in [the issue tracker](https://github.com/SergeyGadzhilov/skvm/issues).
