function Component() {}

Component.prototype.createOperations = function () {
  component.createOperations();
  if (installer.isInstaller()) {
    createShortcut("@TargetDir@/bin/skvm.exe", "@DesktopDir@/skvm.lnk");
    createShortcut("@TargetDir@/bin/skvm.exe", "@StartMenuDir@/skvm.lnk");
    createShortcut(
      "@TargetDir@/maintenancetool.exe",
      "@StartMenuDir@/maintenancetool.lnk"
    );
    addFirewallRules();
    installService();
  }
};

function createShortcut(target, location) {
  component.addOperation(
    "CreateShortcut",
    target,
    location,
    "workingDirectory=@TargetDir@"
  );
}

function addFirewallRule(programm, name, protocol, direction, action) {
  component.addElevatedOperation(
    "Execute",
    "netsh",
    "advfirewall",
    "firewall",
    "add",
    "rule",
    "name=" + name,
    "protocol=" + protocol,
    "dir=" + direction,
    "action=" + action,
    "program=" + programm
  );
}

function getProgrammPath(name) {
  return `program=${installer.value("TargetDir")}/bin/${name}.exe`
    .split("/")
    .join("\\");
}

function addFirewallRules() {
  const programs = [getProgrammPath("skvms.exe"), getProgrammPath("skvmc.exe")];

  programs.forEach((program) => {
    addFirewallRule(program, "@ProductName@", "TCP", "in", "allow");
    addFirewallRule(program, "@ProductName@", "TCP", "out", "allow");
    addFirewallRule(program, "@ProductName@", "UDP", "in", "allow");
    addFirewallRule(program, "@ProductName@", "UDP", "out", "allow");
  });
}

function installService() {
  registerService();
  startService();
}

function registerService() {
  component.addElevatedOperation(
    "Execute",
    "sc",
    "create",
    "skvmd",
    "binPath=@TargetDir@/bin/skvmd.exe",
    "start=auto",
    "UNDOEXECUTE",
    "sc",
    "delete",
    "skvmd"
  );
}

function startService() {
  component.addElevatedOperation(
    "Execute",
    "sc",
    "start",
    "skvmd",
    "UNDOEXECUTE",
    "sc",
    "stop",
    "skvmd"
  );
}
