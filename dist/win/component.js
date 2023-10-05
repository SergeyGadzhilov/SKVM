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

function addFirewallRule(programm, name, protocol, direction) {
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
    "action=allow",
    "program=" + programm,
    "UNDOEXECUTE",
    "netsh",
    "advfirewall",
    "firewall",
    "delete",
    "rule",
    "name=" + name,
    "protocol=" + protocol,
    "dir=" + direction,
    "program=" + programm
  );
}

function getProgrammPath(name) {
  return `${installer.value("TargetDir")}/bin/${name}.exe`
    .split("/")
    .join("\\");
}

function addFirewallRules() {
  const programs = [
    getProgrammPath("skvm"),
    getProgrammPath("skvms"),
    getProgrammPath("skvmc"),
  ];

  programs.forEach((program) => {
    addFirewallRule(program, "@ProductName@", "TCP", "in");
    addFirewallRule(program, "@ProductName@", "TCP", "out");
    addFirewallRule(program, "@ProductName@", "UDP", "in");
    addFirewallRule(program, "@ProductName@", "UDP", "out");
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
