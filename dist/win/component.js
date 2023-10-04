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
  } else if (installer.isUninstaller()) {
    uninstallService();
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

function removeFirewalRule(name) {
  component.addElevatedOperation(
    "Execute",
    "netsh",
    "advfirewall",
    "firewall",
    "delete",
    "rule",
    "name=" + name
  );
}

function removeFirewallRules() {
  const programs = [getProgrammPath("skvms.exe"), getProgrammPath("skvmc.exe")];

  programs.forEach((program) => {
    removeFirewalRule(program, "@ProductName@", "TCP", "in", "allow");
    removeFirewalRule(program, "@ProductName@", "TCP", "out", "allow");
    removeFirewalRule(program, "@ProductName@", "UDP", "in", "allow");
    removeFirewalRule(program, "@ProductName@", "UDP", "out", "allow");
  });
}

function removeService() {
  component.addElevatedOperation("Execute", "sc", "delete", "skvmd");
}

function installService() {
  registerService();
  startService;
}

function uninstallService() {
  stopService();
  removeService();
}

function stopService() {
  component.addElevatedOperation("Execute", "sc", "stop", "skvmd");
}

function registerService() {
  component.addElevatedOperation(
    "Execute",
    "sc",
    "create",
    "skvmd",
    "binPath=@TargetDir@/bin/skvmd.exe",
    "start=auto"
  );
}

function startService() {
  component.addElevatedOperation("Execute", "sc", "start", "skvmd");
}
