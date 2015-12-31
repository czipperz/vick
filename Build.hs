import Development.Shake
import Development.Shake.Command
import Development.Shake.FilePath
import Development.Shake.Util
import Control.Monad
-- import Debug.Trace (trace)
import Data.List (intercalate)
import System.Directory (removeFile)

src, test, srcout, testout, plugins, binary :: FilePath
src = "src"
test = "test"
srcout = "out"
testout = "testout"
plugins = "plugins"
binary = "vick"

cxx, cflags, ldflags :: String
cxx = "clang++"
cflags = "-std=c++11 -g " ++
         "-Wold-style-cast -Wnon-virtual-dtor -Wnarrowing " ++
         "-Wdelete-non-virtual-dtor -Wctor-dtor-privacy " ++
         "-Woverloaded-virtual -Wsign-promo -Wall"
ldflags = "-lboost_regex -lncurses -lpthread"

configFile :: Bool -> String
configFile testing = if testing then "configuration_testing" else "configuration"

main :: IO ()
main = shakeArgs shakeOptions{shakeFiles=srcout, shakeThreads=0} $ do
  want [binary <.> exe]

  phony test $ do
    sources <- getDir True src
    tests <- getDir True test
    let srctoos dir files = [takeAllButDirectory 2 c </> dir </> dropAllButDirectory 1 c -<.> "o" | c <- files]
    let srcos = srctoos srcout sources
    let testos = srctoos testout tests
    let os = srcos ++ testos
    need os
    () <- cmd cxx "-o" [testout </> srcout <.> exe] os ldflags
    cmd $ "./" ++ testout </> srcout <.> exe

  phony "clean" $
    getOutDirectories >>= mapM (flip removeFilesAfter ["//*"]) >>
    removeFilesAfter "." ["//~*", "//#*#", binary]

  phony "doc" $ do
    sources <- getSourceDirectories
    let file = "Doxyfile.edit"
    copyFile' "Doxyfile" file
    liftIO $ appendFile file ("INPUT = src " ++ intercalate [' '] sources ++ "\n")
    Exit _ <- cmd "doxygen" [file]
    liftIO $ removeFile file

  phony "tags" $ do
    files <- getSourceAndHeaders
    cmd "etags" files

  binary <.> exe %> \out -> do
    sources <- getDir False src
    let srctoos dir files = [takeAllButDirectory 2 c </> dir </> dropAllButDirectory 1 c -<.> "o" | c <- files]
    let srcos = srctoos srcout sources
    need srcos
    cmd cxx "-o" [out] srcos ldflags

  "//" ++ testout </> "*.o" %> compile test
  "//" ++ srcout </> "*.o" %> compile src

compile :: FilePath -> FilePath -> Action ()
compile dir out = do
    includeDirectories <- getIncludeDirectories
    let c = takeAllButDirectory 2 out </> dir </> dropAllButDirectory 1 out -<.> "cc"
    let m = out -<.> "m"
    () <- cmd cxx "-c" [c] "-o" [out] cflags "-MMD -MF" [m] includeDirectories
    needMakefileDependencies m

getOutDirectories :: Action [FilePath]
getOutDirectories = do
  dirs <- getDirectoryDirs plugins >>= return . map (plugins </>)
  let dirsOut = map (</> srcout) dirs ++ map (</> testout) dirs
  dirsExist <- filterM doesDirectoryExist dirsOut
  return $ srcout:testout:dirsExist

getSourceDirectories :: Action [FilePath]
getSourceDirectories =
  getDirectoryDirs plugins >>=
  filterM doesDirectoryExist . map (\x -> plugins </> x </> src) >>=
  return . (:) src

getIncludeDirectories :: Action [FilePath]
getIncludeDirectories = do
  dirs <- getDirectoryDirs plugins >>= return . map (plugins </>)
  let dirsSrc = map (</> src) dirs ++ map (</> test) dirs
  dirsSrcExist <- filterM doesDirectoryExist dirsSrc
  return $ map ("-I"++) (src:test:dirsSrcExist)

getSourceAndHeaders :: Action [FilePath]
getSourceAndHeaders =
  getSourceDirectories >>= \dirs ->
  mapM (flip getDirectoryFiles ["//*.cc","//*.hh"]) dirs >>=
  return . concat . map (\(s,l) -> map (s </>) l) . zip dirs

getDir :: Bool -> FilePath -> Action [FilePath]
getDir testing dir = do
  dirs <- getDirectoryFiles dir ["//*.cc"]
  pluginDirs <- getPluginDirs dir
  plugin <- mapM (flip getDirectoryFiles ["//*.cc"]) pluginDirs
  return $ dirsFixed dirs ++ concat (map (\(s,l) -> map (s </>) l) (zip pluginDirs plugin))
  where dirsFixed dirs = let d = map (dir </>) dirs
                         in if dir == src then filter (src </> configFile (not testing) <.> "cc" /=)
                                                   (if testing then filter (src  </> "main.cc" /=) d else d)
                            else if dir == test && not testing then filter (test </> "test_main.cc" /=) d
                                 else d

getPluginDirs :: FilePath -> Action [FilePath]
getPluginDirs dir =
  getDirectoryDirs plugins >>=
  filterM doesDirectoryExist . map (\x -> plugins </> x </> dir)

split :: (Eq a) => a -> [a] -> [[a]]
split = split' []
  where split' ll _ [] = [reverse ll]
        split' ll e (x:xs) | e == x = reverse ll : split' [] e xs
        split' ll e (x:xs) = split' (x:ll) e xs

dropAllBut, takeAllBut :: Int -> [a] -> [a]
dropAllBut i xx = drop (length xx - i) xx
takeAllBut i xx = take (length xx - i) xx

dropDirectory, dropAllButDirectory, takeDirectory, takeAllButDirectory :: Int -> String -> String
dropDirectory = fun drop
dropAllButDirectory = fun dropAllBut
takeDirectory = fun take
takeAllButDirectory = fun takeAllBut
fun :: Foldable f => (t -> [String] -> f String) -> t -> String -> String
fun f n s = let res = f n (split '/' s) in
  if null res then "" else foldr1 (\l r -> l ++ '/' : r) res
