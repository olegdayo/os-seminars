# Containers

TODO: overlayfs, seccomp, capabilities, privielege, mounts, networking (at least as theory)

## LXC

### Launching the container

### Check, which features it has

#### Processes isolation

Check, that we don't have any processes of host in `ps aux`

#### Resource limiting

Check, that we can limit CPU, RAM, disk I/O, etc...

#### Filesystem isolation

Check, that we cannot access host systems files

#### Changing host info

Check, that we cannot get host info (or that it is changed at least)

## Launching your first container with zero abstractions

### Processes isolation

Let's take a look at `/proc`

We will use linux namespaces for it

```go
func setNamespace() error {
	return nil
}
```

### Resource limiting

We will use cgroups for it

```go
func setResourceLimits() error {
	return nil
}
```

### Filesystem isolation

```go
func changeDirectory(path string) error {
	err := syscall.Mkdir(path, 0o777)
	if err != nil {
		return err
	}

	err = syscall.Chroot(path)
	if err != nil {
		return err
	}

	// err = os.Chdir(path)
	// if err != nil {
	// 	return err
	// }

	return nil
}
```

### Add userspace

Due to new filesystem, we don't really have userspace now

We are going to do it manually

```go
// TODO
```

### Changing host info

```go
func updateHost() error {
	return nil
}
```

### Running requested binary

It will be similar to `docker -it`

We will use `exec` syscall to rewrite our processe's .text (executing code)

```go
func run(argv []string) error {
	cmd := exec.Command(argv[0], argv[1:]...)
	cmd.Stdin = os.Stdin
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr

	err := cmd.Run()
	if err != nil {
		return err
	}

	return nil
}
```

## Conclusion

Container is just an isolated Linux process
