-- Minimal config used to generate markdown from norg files

local function root(root)
  local f = debug.getinfo(1, 'S').source:sub(2)
  return vim.fn.fnamemodify(f, ':p:h:h') .. '/' .. (root or '')
end

local function ends_with(str, ending)
  return ending == '' or str:sub(-#ending) == ending
end

local function log(string, ...)
  print(string:format(...))
  print()
end

---@param plugin string
local function load(plugin)
  local name = plugin:match('.*/(.*)')
  local package_root = root('.tests/site/pack/deps/start/')

  if not vim.loop.fs_stat(package_root .. name) then
    print('Installing ' .. plugin)

    vim.fn.mkdir(package_root, 'p')

    vim.fn.system({
      'git',
      'clone',
      '--depth=1',
      'https://github.com/' .. plugin .. '.git',
      package_root .. '/' .. name,
    })
  end
end

local function install_plugins()
  vim.cmd([[set runtimepath=$VIMRUNTIME]])
  vim.opt.runtimepath:append(root())
  vim.opt.packpath = { root('.tests/site') }

  load('nvim-lua/plenary.nvim')
  load('nvim-treesitter/nvim-treesitter')
  load('nvim-neorg/neorg')

  vim.env.XDG_CONFIG_HOME = root('.tests/config')
  vim.env.XDG_DATA_HOME = root('.tests/data')
  vim.env.XDG_STATE_HOME = root('.tests/state')
  vim.env.XDG_CACHE_HOME = root('.tests/cache')
end

local function setup_neorg()
  require('neorg').setup {
    load = {
      ['core.defaults'] = {},
      ['core.export'] = {},
      ['core.export.markdown'] = {}
    }
  }
end

local function enter_file(file)
  local file = vim.fn.fnamemodify(file, ':p')
  local dir = vim.fn.fnamemodify(file, ':h')

  log('Entering file %s', file)

  vim.cmd(('cd %s'):format(dir))
  vim.cmd(('edit %s'):format(file))
end

local function convert_to_md()
  local cmd = ('Neorg export to-file %s.md'):format(vim.fn.expand('%:t:r'))
  vim.cmd(cmd)
end

local function convert_all_to_markdown()
  local allowed_directories = { '.', 'docs' }

  local function skip_predicate(dir)
    return vim.tbl_contains(allowed_directories, dir)
  end

  local opts = {
    depth = 10,
    skip = skip_predicate
  }

  for name, type in vim.fs.dir('.', opts) do
    if type == 'file' and ends_with(name, '.norg') then
      enter_file(name)
      convert_to_md()
    end
  end

  vim.cmd('quit')
end

install_plugins()
setup_neorg()
vim.api.nvim_create_user_command('ConvertAll', convert_all_to_markdown, { nargs = 0 })
